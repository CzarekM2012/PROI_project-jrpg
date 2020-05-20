#include <QApplication>
#include "dialog_window.h"

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 dialog_window d_window;
 d_window.show();
 return app.exec();

}
