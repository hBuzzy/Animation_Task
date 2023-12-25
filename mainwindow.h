#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>

#include <QtCharts/QtCharts>

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

    void moveItems();
    void changeButtonColor();
    void generateColorAimation(QPropertyAnimation *colorAnimation);
    QSplineSeries* generateSeries();

private slots:
    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui_;
    QEasingCurve::Type currentEasingCurve_ = QEasingCurve::Linear;
    QChart *chart_;
    QPropertyAnimation *moveAnimationItem1_;
    QPropertyAnimation *moveAnimationItem2_;
    QPropertyAnimation *moveAnimationItem3_;
    QPropertyAnimation *moveAnimationItem4_;
    QPropertyAnimation *colorAnimation1_;
    QPropertyAnimation *colorAnimation2_;
    QPropertyAnimation *colorAnimation3_;
    QPropertyAnimation *colorAnimation4_;
};
#endif // MAINWINDOW_H
