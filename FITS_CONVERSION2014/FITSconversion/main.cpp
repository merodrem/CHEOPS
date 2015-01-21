#include<QApplication>
#include <QtWidgets>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("data/cheops_logo.png"));

    MainWindow gui;
    gui.show();
    return app.exec();
}
