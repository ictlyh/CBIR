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
        ui->lbRes1->setPixmap(QPixmap::fromImage(*img1));
        iteEnd++;
      }
    if(iteEnd != results.end())
      {
        string tmp = *iteEnd;
        img2->load(QString(tmp.c_str()));
        ui->lbRes2->setPixmap(QPixmap::fromImage(*img2));
        iteEnd++;
      }
    if(iteEnd != results.end())
      {
        string tmp = *iteEnd;
        img3->load(QString(tmp.c_str()));
        ui->lbRes3->setPixmap(QPixmap::fromImage(*img3));
        iteEnd++;
      }
    if(iteEnd != results.end())
      {
        string tmp = *iteEnd;
        img4->load(QString(tmp.c_str()));
        ui->lbRes4->setPixmap(QPixmap::fromImage(*img4));
        iteEnd++;
      }
}

void CBIR::on_pBLibDir_clicked()
{
    QString libDirectory = QFileDialog::getExistingDirectory(this, tr("ѡ��ͼ���Ŀ¼"),tr("."));
    //QDebug << "The lib directory is :" << libDirectory << endl;
    imageLib.setLibDir((char*)libDirectory.toStdString().c_str());
    ui->leLibDir->setText(libDirectory);
}

void CBIR::on_pBLibFile_clicked()
{
    QString libFile = QFileDialog::getOpenFileName(this, tr("ѡ��ͼ����ļ�"), tr("Text (*.txt)"));
    //QDebug << "The lib file is : " << libFile << endl;
    imageLib.setLibFile((char*)libFile.toStdString().c_str());
    ui->leLibFile->setText(libFile);
}

void CBIR::on_pBBuildLib_clicked()
{
    // ����ͼ��������
    imageLib.buildImageLib();
}

void CBIR::on_pBLoadLib_clicked()
{
    // ����ͼ���������ļ�
    imageLib.loadImageLib();
}

void CBIR::on_pBSetQuery_clicked()
{
    QString query = QFileDialog::getOpenFileName(this, tr("ѡ���ѯͼ��"), ".", tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    // �� lbQueryImage ����ʾͼ�񣬲�������ѯͼ��
    QImage * img = new QImage();
    if(!img->load(query))
      {
        QMessageBox::information(this, tr("��ͼ��ʧ��"), tr("��ͼ��ʧ��!"));
        delete img;
        return;
      }
    ui->lbQueryImage->setPixmap(QPixmap::fromImage(*img));
    queryImage.setPath(query.toStdString());
    queryImage.calcFeature();
}

void CBIR::on_pBSearch_clicked()
{
    // ��������ʾ���
    results = searcher.search(queryImage, imageLib);
    //QDebug << "The result is :" << results << endl;
    iteBegin = results.begin();
    showResults();
}

void CBIR::on_pBReSearch_clicked()
{
  // ��λ�ȡ����ͼ��??
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
        QMessageBox::information(this, tr("�Ѿ��ǵ�һҳ"),tr("�Ѿ��ǵ�һҳ"));
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
      QMessageBox::information(this, tr("�Ѿ������һҳ"), tr("�Ѿ������һҳ"));
      return ;
    }
  iteBegin = iteEnd;
  showResults();
}
