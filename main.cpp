#include "mainwindow/mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow mw;
    mw.show();
    return QApplication::exec();
}
