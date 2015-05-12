#include "cbir.h"
#include "ui_cbir.h"
#include <QFileDialog>

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

void CBIR::on_pBLibDir_clicked()
{
    QString libDirectory = QFileDialog::getExistingDirectory(this, tr("选择图像库目录"),".");
    //QDebug << "The lib directory is :" << libDirectory << endl;
    imageLib.setLibDir(libDirectory);
}

void CBIR::on_pBLibFile_clicked()
{
    QString libFile = QFileDialog::getOpenFileName(this, tr("选择图像库文件"), tr("Text (*.txt)"));
    //QDebug << "The lib file is : " << libFile << endl;
    imageLib.setLibFile(libFile);
}

void CBIR::on_pBBuildLib_clicked()
{
    // 根据 pBLibDir 传过来的 libDirectory 构建图像特征库
    imageLib.buildImageLib();
}

void CBIR::on_pBLoadLib_clicked()
{
    // 根据 pBLibFile 传过来的 libFile 加载图像特征库文件
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
    // 检索并返回结果
    list<string> results = searcher.search(queryImage, imageLib);
    QDebug << "The result is :" << results << endl;
}

void CBIR::on_pBReSearch_clicked()
{
    list<string> feedback;
    list<string> results = searcher.reSearch(queryImage, feedback, imageLib);
    QDebug << "The result is :" << results << endl;
}
