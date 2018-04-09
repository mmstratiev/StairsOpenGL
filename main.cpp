#include <QApplication>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //creates the main window and shows it
    MainWindow *w = new MainWindow;
    w->show();

    return a.exec();
}
