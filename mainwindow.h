// В mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QComboBox>

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
    void curvePreviewChanged(int index);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene_;
    AnimatedItem *animatedItem_;
    QComboBox *curveComboBox_;

};

#endif // MAINWINDOW_H
