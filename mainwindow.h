// В mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>  // Добавленный заголовочный файл
#include "animateditem.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateStatusBar(qreal value);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene_;
    AnimatedItem *animatedItem_;
};

#endif // MAINWINDOW_H
