#include <QApplication>
#include "Atzar.h"

int main (int argc, char **argv)
{
  QApplication a( argc, argv);

  Atzar myf(0);
  myf.show();

  return a.exec ();
}

