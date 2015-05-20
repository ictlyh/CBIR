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
  ImageLib imageLib;      // 特征图像库
  Searcher searcher;      // 搜索器
  Image queryImage;       // 检索图像
  list<string> results;   // 检索结果图像路径列表
  list<string> feedback;  // 反馈图像路径列表
  int begin, end;         // 结果显示中的开始和结束index
};

#endif // CBIR_H
