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
        img1->load(*iteEnd);
        ui->lbRes1->setPixmap(QPixmap::fromImage(*img1));
        iteEnd++;
      }
    if(iteEnd != results.end())
      {
        img2->load(*iteEnd);
        ui->lbRes2->setPixmap(QPixmap::fromImage(*img2));
        iteEnd++;
      }
    if(iteEnd != results.end())
      {
        img3->load(*iteEnd);
        ui->lbRes3->setPixmap(QPixmap::fromImage(*img3));
        iteEnd++;
      }
    if(iteEnd != results.end())
      {
        img4->load(*iteEnd);
        ui->lbRes4->setPixmap(QPixmap::fromImage(*img4));
        iteEnd++;
      }
}

void CBIR::on_pBLibDir_clicked()
{
    QString libDirectory = QFileDialog::getExistingDirectory(this, tr("选择图像库目录"),".");
    //QDebug << "The lib directory is :" << libDirectory << endl;
    imageLib.setLibDir(libDirectory);
    ui->leLibDir->setText(libDirectory);
}

void CBIR::on_pBLibFile_clicked()
{
    QString libFile = QFileDialog::getOpenFileName(this, tr("选择图像库文件"), tr("Text (*.txt)"));
    //QDebug << "The lib file is : " << libFile << endl;
    imageLib.setLibFile(libFile);
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
    QString query = QFileDialog::getOpenFileName(this, tr("选择查询图像"), ".", tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    // 在 lbQueryImage 中显示图像，并构建查询图像
    QImage * img = new QImage();
    if(!img->load(query))
      {
        QMessageBox::information(this, tr("打开图像失败"), tr("打开图像失败!"));
        delete img;
        return;
      }
    ui->lbQueryImage->setPixmap(QPixmap::fromImage(*img));
    queryImage.setPath(query);
    queryImage.calcFeature();
}

void CBIR::on_pBSearch_clicked()
{
    // 检索并显示结果
    results = searcher.search(queryImage, imageLib);
    QDebug << "The result is :" << results << endl;
    iteBegin = results.begin();
    showResults();
}

void CBIR::on_pBReSearch_clicked()
{
  // 如何获取反馈图像??
    list<string> feedback;
    results = searcher.reSearch(queryImage, feedback, imageLib);
    QDebug << "The result is :" << results << endl;
    iteBegin = results.begin();
    showResults();
}

void CBIR::on_pBUp_clicked()
{
    if(iteBegin == results.begin())
      {
        QMessageBox::information(this, tr("已经是第一页"),tr("已经是第一页"));
        return ;
      }
    iteBegin -= 4;
    showResults();
}

void CBIR::on_pBNext_clicked()
{
  if(iteEnd == results.end())
    {
      QMessageBox::information(this, tr("已经是最后一页"), tr("已经是最后一页"));
      return ;
    }
  iteBegin = iteEnd;
  showResults();
}
