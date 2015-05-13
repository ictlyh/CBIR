#include "cbir.h"
#include "ui_cbir.h"
#include <QFileDialog>
#include <QMessageBox>

CBIR::CBIR(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::CBIR)
{
    ui->setupUi(this);
}

CBIR::~CBIR()
{
    delete ui;
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
        img1->load(QString(tmp.c_str()));
        *img1 = img1->scaled(ui->lbRes1->size(), Qt::KeepAspectRatio);
        ui->lbRes1->setPixmap(QPixmap::fromImage(*img1));
        iteEnd++;
      }
    if(iteEnd != results.end())
      {
        string tmp = *iteEnd;
        img2->load(QString(tmp.c_str()));
        *img2 = img2->scaled(ui->lbRes2->size(), Qt::KeepAspectRatio);
        ui->lbRes2->setPixmap(QPixmap::fromImage(*img2));
        iteEnd++;
      }
    if(iteEnd != results.end())
      {
        string tmp = *iteEnd;
        img3->load(QString(tmp.c_str()));
        *img3 = img3->scaled(ui->lbRes3->size(), Qt::KeepAspectRatio);
        ui->lbRes3->setPixmap(QPixmap::fromImage(*img3));
        iteEnd++;
      }
    if(iteEnd != results.end())
      {
        string tmp = *iteEnd;
        img4->load(QString(tmp.c_str()));
        *img4 = img4->scaled(ui->lbRes4->size(), Qt::KeepAspectRatio);
        ui->lbRes4->setPixmap(QPixmap::fromImage(*img4));
        iteEnd++;
      }
}

void CBIR::on_pBLibDir_clicked()
{
    QString libDirectory = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("选择图像库目录"),QString::fromLocal8Bit("."));
    //QDebug << "The lib directory is :" << libDirectory << endl;
    imageLib.setLibDir((char*)libDirectory.toStdString().c_str());
    ui->leLibDir->setText(libDirectory);
}

void CBIR::on_pBLibFile_clicked()
{
    QString libFile = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择图像库文件"), QString::fromLocal8Bit("Text (*.txt)"));
    //QDebug << "The lib file is : " << libFile << endl;
    imageLib.setLibFile((char*)libFile.toStdString().c_str());
    ui->leLibFile->setText(libFile);
}

void CBIR::on_pBBuildLib_clicked()
{
    // 构建图像特征库
    imageLib.buildImageLib();
}

void CBIR::on_pBLoadLib_clicked()
{
    // 加载图像特征库文件
    imageLib.loadImageLib();
}

void CBIR::on_pBSetQuery_clicked()
{
    QString query = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择查询图像"), ".", QString::fromLocal8Bit("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
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
    queryImage.setPath(query.toStdString());
    queryImage.calcFeature();
}

void CBIR::on_pBSearch_clicked()
{
    // 检索并显示结果
    results = searcher.search(queryImage, imageLib);
    //QDebug << "The result is :" << results << endl;
    iteBegin = results.begin();
    showResults();
}

void CBIR::on_pBReSearch_clicked()
{
  // 如何获取反馈图像??
    list<string> feedback;
    results = searcher.reSearch(queryImage, feedback, imageLib);
    //QDebug << "The result is :" << results << endl;
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
