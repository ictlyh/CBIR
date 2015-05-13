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
    queryImage.setPath("");
    imageLib.setLibDir("");
    results.clear();
    begin = 0;
    end = 0;
}

CBIR::~CBIR()
{
    delete ui;
}

void CBIR::showResults()
{
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
    QString libDirectory = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("ѡ��ͼ���Ŀ¼"));
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
    QString libFile = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("ѡ��ͼ����ļ�"));
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
        QMessageBox::information(this, QString::fromLocal8Bit("��ѡ��ͼ���·��"), QString::fromLocal8Bit("��ѡ��ͼ���·��"));
        return ;
      }
    // ����ͼ��������
    imageLib.buildImageLib();
    QMessageBox::information(this, QString::fromLocal8Bit("�������������"), QString::fromLocal8Bit("�������������"));
    // ����ͼ��������
    imageLib.saveImageLib();
    //QMessageBox::information(this, QString::fromLocal8Bit("ͼ����ģ"), QString("%1").arg(imageLib.getImageList().size()));
}

void CBIR::on_pBLoadLib_clicked()
{
    // ����ͼ���������ļ�
    if(imageLib.loadImageLib())
      {
        QMessageBox::information(this, QString::fromLocal8Bit("�������������"), QString::fromLocal8Bit("�������������"));
      }
    else
      {
        QMessageBox::information(this, QString::fromLocal8Bit("����������ʧ��"), QString(imageLib.getLibFile()));
      }
}

void CBIR::on_pBSetQuery_clicked()
{
    QString query = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("ѡ���ѯͼ��"), ".", QString::fromLocal8Bit("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    // Press Cancle
    if(query == NULL)
      return ;
    // �� lbQueryImage ����ʾͼ�񣬲�������ѯͼ��
    QImage * img = new QImage();
    if(!img->load(query))
      {
        QMessageBox::information(this, QString::fromLocal8Bit("��ͼ��ʧ��"), QString::fromLocal8Bit("��ͼ��ʧ��!"));
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
       QMessageBox::information(this, QString::fromLocal8Bit("��ѡ�����ͼ��"), QString::fromLocal8Bit("��ѡ�����ͼ��"));
       return ;
    }
    // ��������ʾ���
    searcher.setTopK(8);
    results = searcher.search(queryImage, imageLib);
    //QMessageBox::information(this, QString::fromLocal8Bit("���������Ŀ"), QString("%1").arg(results.size()));
    begin = 0;
    showResults();
}

void CBIR::on_pBReSearch_clicked()
{
    if(strlen(queryImage.getPath()) == 0)
    {
       QMessageBox::information(this, QString::fromLocal8Bit("��ѡ�����ͼ��"), QString::fromLocal8Bit("��ѡ�����ͼ��"));
       return ;
    }
    // ��λ�ȡ����ͼ��??
    list<string> feedback;
    results = searcher.reSearch(queryImage, feedback, imageLib);
    begin = 0;
    showResults();
}

void CBIR::on_pBUp_clicked()
{
    if(begin == 0)
      {
        QMessageBox::information(this, QString::fromLocal8Bit("�Ѿ��ǵ�һҳ"), QString::fromLocal8Bit("�Ѿ��ǵ�һҳ"));
        return ;
      }
    begin = begin - 4;
    showResults();
}

void CBIR::on_pBNext_clicked()
{
  if(end == results.size())
    {
      QMessageBox::information(this, QString::fromLocal8Bit("�Ѿ������һҳ"), QString::fromLocal8Bit("�Ѿ������һҳ"));
      return ;
    }
  begin = end;
  showResults();
}
