#include "cbir.h"
#include "ui_cbir.h"
#include <QFileDialog>
#include <QMessageBox>

CBIR::CBIR(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::CBIR)
{
    ui->setupUi(this);
    queryImage.setPath("");
    imageLib.setLibDir("");
    results.clear();
    iteBegin = results.begin();
    iteEnd = results.begin();
}

CBIR::~CBIR()
{
    delete ui;
}

string CBIR::convertToString(QString src)
{
    QString tmp(src);
    if(tmp.contains("/"))
      tmp.replace("/", "\\", Qt::CaseInsensitive);
    return tmp.toStdString();
}

QString CBIR::convertToQString(string src)
{
    QString tmp(QString::fromLocal8Bit(src.c_str()));
    if(tmp.contains("\\"))
      tmp.replace("\\", "/", Qt::CaseInsensitive);
    return tmp;
}

void CBIR::showResults()
{
    iteEnd = iteBegin;
    QImage *img1 = new QImage();
    QImage *img2 = new QImage();
    QImage *img3 = new QImage();
    QImage *img4 = new QImage();
    if(iteEnd != results.end())
      {
        string tmp = *iteEnd;
        img1->load(convertToQString(tmp));
        *img1 = img1->scaled(ui->lbRes1->size(), Qt::KeepAspectRatio);
        ui->lbRes1->setPixmap(QPixmap::fromImage(*img1));
        iteEnd++;
      }
    if(iteEnd != results.end())
      {
        string tmp = *iteEnd;
        img2->load(convertToQString(tmp));
        *img2 = img2->scaled(ui->lbRes2->size(), Qt::KeepAspectRatio);
        ui->lbRes2->setPixmap(QPixmap::fromImage(*img2));
        iteEnd++;
      }
    if(iteEnd != results.end())
      {
        string tmp = *iteEnd;
        img3->load(convertToQString(tmp));
        *img3 = img3->scaled(ui->lbRes3->size(), Qt::KeepAspectRatio);
        ui->lbRes3->setPixmap(QPixmap::fromImage(*img3));
        iteEnd++;
      }
    if(iteEnd != results.end())
      {
        string tmp = *iteEnd;
        img4->load(convertToQString(tmp));
        *img4 = img4->scaled(ui->lbRes4->size(), Qt::KeepAspectRatio);
        ui->lbRes4->setPixmap(QPixmap::fromImage(*img4));
        iteEnd++;
      }
}

void CBIR::on_pBLibDir_clicked()
{
    QString libDirectory = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("选择图像库目录"));
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
    QString libFile = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择图像库文件"), QString::fromLocal8Bit("Text (*.txt)"));
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
    imageLib.buildImageLib();
    QMessageBox::information(this, QString::fromLocal8Bit("构建特征库完成"), QString::fromLocal8Bit("构建特征库完成"));
    // 保存图像特征库
    imageLib.saveImageLib();
    QMessageBox::information(this, QString::fromLocal8Bit("图像库规模"), QString("%1").arg(imageLib.getImageList().size()));
}

void CBIR::on_pBLoadLib_clicked()
{
    // 加载图像特征库文件
    if(imageLib.loadImageLib())
      {
        QMessageBox::information(this, QString::fromLocal8Bit("加载特征库完成"), QString::fromLocal8Bit("加载特征库完成"));
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
    // 检索并显示结果
    results = searcher.search(queryImage, imageLib);
    QMessageBox::information(this, QString::fromLocal8Bit("检索结果数目"), QString("%1").arg(results.size()));
    iteBegin = results.begin();
    showResults();
}

void CBIR::on_pBReSearch_clicked()
{
    // 如何获取反馈图像??
    list<string> feedback;
    results = searcher.reSearch(queryImage, feedback, imageLib);
    iteBegin = results.begin();
    showResults();
}

void CBIR::on_pBUp_clicked()
{
    if(iteBegin == results.begin())
      {
        QMessageBox::information(this, QString::fromLocal8Bit("已经是第一页"), QString::fromLocal8Bit("已经是第一页"));
        return ;
      }
    iteBegin = iteBegin--;
    iteBegin = iteBegin--;
    iteBegin = iteBegin--;
    iteBegin = iteBegin--;
    showResults();
}

void CBIR::on_pBNext_clicked()
{
  if(iteEnd == results.end())
    {
      QMessageBox::information(this, QString::fromLocal8Bit("已经是最后一页"), QString::fromLocal8Bit("已经是最后一页"));
      return ;
    }
  iteBegin = iteEnd;
  showResults();
}
