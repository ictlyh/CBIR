#ifndef CBIR_H
#define CBIR_H

#include <QMainWindow>
#include "ImageLib.h"
#include "Searcher.h"
#include "Image.h"

namespace Ui {
  class CBIR;
}

class CBIR : public QMainWindow
{
  Q_OBJECT

public:
  explicit CBIR(QWidget *parent = 0);
  ~CBIR();

  void showResults();

private slots:
  void on_pBLibDir_clicked();

  void on_pBLibFile_clicked();

  void on_pBBuildLib_clicked();

  void on_pBLoadLib_clicked();

  void on_pBSetQuery_clicked();

  void on_pBSearch_clicked();

  void on_pBReSearch_clicked();

  void on_pBUp_clicked();

  void on_pBNext_clicked();

  void on_checkBox1_stateChanged(int arg1);

  void on_checkBox2_stateChanged(int arg1);

  void on_checkBox3_stateChanged(int arg1);

  void on_checkBox4_stateChanged(int arg1);

  void on_actionHelp_triggered();

private:
  Ui::CBIR *ui;           // GUI
  ImageLib imageLib;      // ����ͼ���
  Searcher searcher;      // ������
  Image queryImage;       // ����ͼ��
  list<string> results;   // �������ͼ��·���б�
  list<string> feedback;  // ����ͼ��·���б�
  int begin, end;         // �����ʾ�еĿ�ʼ�ͽ���index
};

#endif // CBIR_H
