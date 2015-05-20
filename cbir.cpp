#include "cbir.h"
#include "ui_cbir.h"
#include <QFileDialog>
#include <QMessageBox>
#include "methods.h"

CBIR::CBIR(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::CBIR)
{
    ui->setupUi(this);
    // 初始化
    queryImage.setPath("");
    imageLib.setLibDir("");
    results.clear();
    feedback.clear();
    begin = 0;
    end = 0;
    ui->leColorWeight->setText(QString("%1").arg(searcher.getColorWeight()));
    ui->statusBar->clearMessage();
}

CBIR::~CBIR()
{
    delete ui;
}

void CBIR::showResults()
{
    ui->statusBar->showMessage(QString::fromLocal8Bit("正在显示检索结果..."));
    list<string>::iterator ite = results.begin();
    for(int i = 0; i < begin; i++,ite++)
      ;
    end = begin;
    QImage *img1 = new QImage();
    QImage *img2 = new QImage();
    QImage *img3 = new QImage();
    QImage *img4 = new QImage();
    if(ite != results.end())
      {
        img1->load(convertToQString(*ite));
        *img1 = img1->scaled(ui->lbRes1->size(), Qt::KeepAspectRatio);
        ui->lbRes1->setPixmap(QPixmap::fromImage(*img1));
        ite++;
        end++;
      }
    if(ite != results.end())
      {
        img2->load(convertToQString(*ite));
        *img2 = img2->scaled(ui->lbRes2->size(), Qt::KeepAspectRatio);
        ui->lbRes2->setPixmap(QPixmap::fromImage(*img2));
        ite++;
        end++;
      }
    if(ite != results.end())
      {
        img3->load(convertToQString(*ite));
        *img3 = img3->scaled(ui->lbRes3->size(), Qt::KeepAspectRatio);
        ui->lbRes3->setPixmap(QPixmap::fromImage(*img3));
        ite++;
        end++;
      }
    if(ite != results.end())
      {
        img4->load(convertToQString(*ite));
        *img4 = img4->scaled(ui->lbRes4->size(), Qt::KeepAspectRatio);
        ui->lbRes4->setPixmap(QPixmap::fromImage(*img4));
        ite++;
        end++;
      }    
}

void CBIR::on_pBLibDir_clicked()
{
    QString libDirectory = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("选择图像库目录"), ".");
    // Press Cancle
    if(libDirectory == NULL)
      return ;
    char tmp[256];
    strcpy_s(tmp, convertToString(libDirectory).c_str());
    imageLib.setLibDir(tmp);
    ui->leLibDir->setText(libDirectory);
}

void CBIR::on_pBLibFile_clicked()
{
    QString libFile = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择图像库文件"), ".", QString::fromLocal8Bit("Text (*.txt)"));
    // Press Cancle
    if(libFile == NULL)
      return ;
    char tmp[256];
    strcpy_s(tmp, convertToString(libFile).c_str());
    imageLib.setLibFile(tmp);
    ui->leLibFile->setText(libFile);
}

void CBIR::on_pBBuildLib_clicked()
{
    if(strlen(imageLib.getLibDir()) == 0)
      {
        QMessageBox::information(this, QString::fromLocal8Bit("请选择图像库路径"), QString::fromLocal8Bit("请选择图像库路径"));
        return ;
      }
    // 构建图像特征库
    ui->statusBar->showMessage(QString::fromLocal8Bit("正在构建图像特征库，请耐心等待..."));
    imageLib.buildImageLib();
    QMessageBox::information(this, QString::fromLocal8Bit("构建特征库完成"), QString::fromLocal8Bit("构建特征库完成"));
    // 保存图像特征库
    ui->statusBar->showMessage(QString::fromLocal8Bit("正在将图像特征库写入文件，请耐心等待..."));
    imageLib.saveImageLib();
    ui->statusBar->showMessage(QString::fromLocal8Bit("图像特征库写入文件完成"));
}

void CBIR::on_pBLoadLib_clicked()
{
    // 加载图像特征库文件
    ui->statusBar->showMessage(QString::fromLocal8Bit("正在加载图像特征库，请耐心等待..."));
    if(imageLib.loadImageLib())
      {
        QMessageBox::information(this, QString::fromLocal8Bit("加载特征库完成"), QString::fromLocal8Bit("加载特征库完成"));
        ui->statusBar->clearMessage();
      }
    else
      {
        QMessageBox::information(this, QString::fromLocal8Bit("加载特征库失败"), QString(imageLib.getLibFile()));
      }
}

void CBIR::on_pBSetQuery_clicked()
{
    QString query = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择查询图像"), ".", QString::fromLocal8Bit("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    // Press Cancle
    if(query == NULL)
      return ;
    // 在 lbQueryImage 中显示图像，并构建查询图像
    QImage * img = new QImage();
    if(!img->load(query))
      {
        QMessageBox::information(this, QString::fromLocal8Bit("打开图像失败"), QString::fromLocal8Bit("打开图像失败!"));
        delete img;
        return;
      }
    *img = img->scaled(ui->lbQueryImage->size(), Qt::KeepAspectRatio);
    ui->lbQueryImage->setPixmap(QPixmap::fromImage(*img));
    queryImage.setPath(convertToString(query));
    queryImage.calcFeature();
    delete img;
}

void CBIR::on_pBSearch_clicked()
{
    if(strlen(queryImage.getPath()) == 0)
    {
       QMessageBox::information(this, QString::fromLocal8Bit("请选择检索图像"), QString::fromLocal8Bit("请选择检索图像"));
       return ;
    }
    // 设置权重
    bool flag;
    float colorWeight = ui->leColorWeight->text().toFloat(&flag);
    if(!flag || colorWeight < 0 || colorWeight > 1)
      {
        QMessageBox::information(this, QString::fromLocal8Bit("请设置有效权重"), QString::fromLocal8Bit("有效区间[0.0,1.0]"));
        return ;
      }
    searcher.setColorWeight(colorWeight);
    searcher.setShapeWeight(1 - colorWeight);
    // 检索并显示结果
    ui->statusBar->showMessage(QString::fromLocal8Bit("正在查询，请耐心等待..."));
    results.clear();
    results = searcher.search(queryImage, imageLib);
    // 清空现有的显示
    ui->lbRes1->clear();
    ui->lbRes2->clear();
    ui->lbRes3->clear();
    ui->lbRes4->clear();
    begin = 0;
    showResults();
    // 清空反馈情况
    feedback.clear();
    ui->checkBox1->setCheckState(Qt::Unchecked);
    ui->checkBox2->setCheckState(Qt::Unchecked);
    ui->checkBox3->setCheckState(Qt::Unchecked);
    ui->checkBox4->setCheckState(Qt::Unchecked);
}

void CBIR::on_pBReSearch_clicked()
{
    if(strlen(queryImage.getPath()) == 0)
    {
       QMessageBox::information(this, QString::fromLocal8Bit("请选择检索图像"), QString::fromLocal8Bit("请选择检索图像"));
       return ;
    }
    // 设置权重
    bool flag;
    float colorWeight = ui->leColorWeight->text().toFloat(&flag);
    if(!flag || colorWeight < 0 || colorWeight > 1)
      {
        QMessageBox::information(this, QString::fromLocal8Bit("请设置有效权重"), QString::fromLocal8Bit("有效区间[0.0,1.0]"));
        return ;
      }
    searcher.setColorWeight(colorWeight);
    searcher.setShapeWeight(1 - colorWeight);
    // 清空之前检索结果重新检索
    ui->statusBar->showMessage(QString::fromLocal8Bit("正在查询，请耐心等待..."));
    results.clear();
    results = searcher.reSearch(queryImage, feedback, imageLib);
    // 清空现有的显示
    ui->lbRes1->clear();
    ui->lbRes2->clear();
    ui->lbRes3->clear();
    ui->lbRes4->clear();
    begin = 0;
    showResults();
    // 清空反馈情况
    feedback.clear();
    ui->checkBox1->setCheckState(Qt::Unchecked);
    ui->checkBox2->setCheckState(Qt::Unchecked);
    ui->checkBox3->setCheckState(Qt::Unchecked);
    ui->checkBox4->setCheckState(Qt::Unchecked);
}

void CBIR::on_pBUp_clicked()
{
    if(begin == 0)
      {
        QMessageBox::information(this, QString::fromLocal8Bit("已经是第一页"), QString::fromLocal8Bit("已经是第一页"));
        return ;
      }
    // 清空现有的显示
    ui->lbRes1->clear();
    ui->lbRes2->clear();
    ui->lbRes3->clear();
    ui->lbRes4->clear();
    begin = begin - 4;
    showResults();
    list<string>::iterator ite = results.begin();
    string path;
    for(int i = 0; i < begin && ite != results.end(); i++, ite++)
      ;
    if(ite == results.end())
        return ;
    else
      {
        path = *ite;
        if(containsString(feedback, path))
          ui->checkBox1->setCheckState(Qt::Checked);
        else
          ui->checkBox1->setCheckState(Qt::Unchecked);
      }
    ite++;
    if(ite == results.end())
        return ;
    else
      {
        path = *ite;
        if(containsString(feedback, path))
          ui->checkBox2->setCheckState(Qt::Checked);
        else
          ui->checkBox2->setCheckState(Qt::Unchecked);
      }
    ite++;
    if(ite == results.end())
        return ;
    else
      {
        path = *ite;
        if(containsString(feedback, path))
          ui->checkBox3->setCheckState(Qt::Checked);
        else
          ui->checkBox3->setCheckState(Qt::Unchecked);
      }
    ite++;
    if(ite == results.end())
        return ;
    else
      {
        path = *ite;
        if(containsString(feedback, path))
          ui->checkBox4->setCheckState(Qt::Checked);
        else
          ui->checkBox4->setCheckState(Qt::Unchecked);
      }
}

void CBIR::on_pBNext_clicked()
{
  if(end == results.size())
    {
      QMessageBox::information(this, QString::fromLocal8Bit("已经是最后一页"), QString::fromLocal8Bit("已经是最后一页"));
      return ;
    }
  // 清空现有的显示
  ui->lbRes1->clear();
  ui->lbRes2->clear();
  ui->lbRes3->clear();
  ui->lbRes4->clear();
  begin = end;
  showResults();
  list<string>::iterator ite = results.begin();
  string path;
  for(int i = 0; i < begin && ite != results.end(); i++, ite++)
    ;
  if(ite == results.end())
      return ;
  else
    {
      path = *ite;
      if(containsString(feedback, path))
        ui->checkBox1->setCheckState(Qt::Checked);
      else
        ui->checkBox1->setCheckState(Qt::Unchecked);
    }
  ite++;
  if(ite == results.end())
      return ;
  else
    {
      path = *ite;
      if(containsString(feedback, path))
        ui->checkBox2->setCheckState(Qt::Checked);
      else
        ui->checkBox2->setCheckState(Qt::Unchecked);
    }
  ite++;
  if(ite == results.end())
      return ;
  else
    {
      path = *ite;
      if(containsString(feedback, path))
        ui->checkBox3->setCheckState(Qt::Checked);
      else
        ui->checkBox3->setCheckState(Qt::Unchecked);
    }
  ite++;
  if(ite == results.end())
      return ;
  else
    {
      path = *ite;
      if(containsString(feedback, path))
        ui->checkBox4->setCheckState(Qt::Checked);
      else
        ui->checkBox4->setCheckState(Qt::Unchecked);
    }
}

void CBIR::on_checkBox1_stateChanged(int arg1)
{
  list<string>::iterator ite = results.begin();
  for(int i = 0; i < begin && ite != results.end(); i++, ite++)
    ;
  if(ite == results.end())
    return ;
  if(arg1 == 0 && containsString(feedback, *ite))
    feedback.remove(*ite);
  if(arg1 == 2 && !containsString(feedback, *ite))
    feedback.push_back(*ite);
}

void CBIR::on_checkBox2_stateChanged(int arg1)
{
  list<string>::iterator ite = results.begin();
  for(int i = 0; i < begin + 1 && ite != results.end(); i++, ite++)
    ;
  if(ite == results.end())
    return ;
  if(arg1 == 0 && containsString(feedback, *ite))
    feedback.remove(*ite);
  if(arg1 == 2 && !containsString(feedback, *ite))
    feedback.push_back(*ite);
}

void CBIR::on_checkBox3_stateChanged(int arg1)
{
  list<string>::iterator ite = results.begin();
  for(int i = 0; i < begin + 2 && ite != results.end(); i++, ite++)
    ;
  if(ite == results.end())
    return ;
  if(arg1 == 0 && containsString(feedback, *ite))
    feedback.remove(*ite);
  if(arg1 == 2 && !containsString(feedback, *ite))
    feedback.push_back(*ite);
}

void CBIR::on_checkBox4_stateChanged(int arg1)
{
  list<string>::iterator ite = results.begin();
  for(int i = 0; i < begin + 3 && ite != results.end(); i++, ite++)
    ;
  if(ite == results.end())
    return ;
  if(arg1 == 0 && containsString(feedback, *ite))
    feedback.remove(*ite);
  if(arg1 == 2 && !containsString(feedback, *ite))
    feedback.push_back(*ite);
}

void CBIR::on_actionHelp_triggered()
{
    QString content;
    content.append(QString::fromLocal8Bit("使用前请先阅读 Readme.html 文件"));
    content.append("\n");
    content.append(QString::fromLocal8Bit("源代码:https://github.com/ictlyh/CBIR"));
    content.append("\n");
    content.append(QString::fromLocal8Bit("Powered by: 罗远浩 黄博阳"));
    QMessageBox::information(this, QString::fromLocal8Bit("Help"), content);
}
