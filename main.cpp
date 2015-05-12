#include "cbir.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QTextCodec *codec = QTextCodec::codecForName("GBK");
  QTextCodec::setCodecForLocale(codec);
  CBIR w;
  w.show();

  return a.exec();
}
