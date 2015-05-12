#include "cbir.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  CBIR w;
  w.show();

  return a.exec();
}
