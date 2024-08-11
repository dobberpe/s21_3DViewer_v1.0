#include <QApplication>

#include "graphics.h"
#include "main_window.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  main_window w;
  w.show();
  // Viewer w;
  // w.show();
  return a.exec();
}
