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

private:
  Ui::CBIR *ui;
  ImageLib imageLib;
  Searcher searcher;
  Image queryImage;
  list<string> results;
  int begin, end;
};

#endif // CBIR_H
