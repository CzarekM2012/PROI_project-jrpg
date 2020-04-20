#include "mainmenu.h"

#include <QApplication>
#include <QScreen>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow main_window;
    main_window.setGeometry(QGuiApplication::primaryScreen()->geometry());
    MainMenu menu(&main_window);
    main_window.setCentralWidget(&menu);
    main_window.showFullScreen();
    return app.exec();
}
