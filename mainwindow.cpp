#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>
#include <cmath>

#include <QtCharts/QtCharts>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow) {
    ui_->setupUi(this);

    moveAnimationItem1_ = new QPropertyAnimation(ui_->pushButton, "geometry");
    moveAnimationItem1_->setDuration(2000);
    moveAnimationItem2_ = new QPropertyAnimation(ui_->pushButton_2, "geometry");
    moveAnimationItem2_->setDuration(2000);
    moveAnimationItem3_ = new QPropertyAnimation(ui_->pushButton_3, "geometry");
    moveAnimationItem3_->setDuration(2000);
    moveAnimationItem4_ = new QPropertyAnimation(ui_->pushButton_4, "geometry");
    moveAnimationItem4_->setDuration(2000);

    colorAnimation1_ = new QPropertyAnimation(ui_->pushButton, "color");
    colorAnimation2_ = new QPropertyAnimation(ui_->pushButton_2, "color");
    colorAnimation3_ = new QPropertyAnimation(ui_->pushButton_3, "color");
    colorAnimation4_ = new QPropertyAnimation(ui_->pushButton_4, "color");

   connect(ui_->animationButton, &QPushButton::clicked, this, &MainWindow::moveItems);
   connect(ui_->animationButton, &QPushButton::clicked, this, &MainWindow::changeButtonColor);

   ui_->comboBox->addItem("Linear");
   ui_->comboBox->addItem("OutQuad");
   ui_->comboBox->addItem("InElastic");

   chart_ = new QChart();

   QSplineSeries *series = generateSeries();
   chart_->addSeries(series);
   chart_->legend()->hide();

   QChartView *chartView = new QChartView(chart_);
   chartView->setRenderHint(QPainter::Antialiasing);

   QValueAxis *axisX = new QValueAxis();
   axisX->setTitleText("x");
   axisX->setTickCount(1);
   chart_->addAxis(axisX, Qt::AlignBottom);
   series->attachAxis(axisX);

   QValueAxis *axisY = new QValueAxis();
   axisY->setTitleText("y");
   axisY->setTickCount(1);
   chart_->addAxis(axisY, Qt::AlignLeft);
   series->attachAxis(axisY);

    ui_->verticalLayout->addWidget(chartView);
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::moveItems() {
    moveAnimationItem1_->setStartValue(ui_->pushButton->geometry());
    moveAnimationItem1_->setEndValue(ui_->pushButton_2->geometry());
    moveAnimationItem1_->setEasingCurve(currentEasingCurve_);
    moveAnimationItem1_->start();

    moveAnimationItem2_->setStartValue(ui_->pushButton_2->geometry());
    moveAnimationItem2_->setEndValue(ui_->pushButton_3->geometry());
    moveAnimationItem2_->setEasingCurve(currentEasingCurve_);
    moveAnimationItem2_->start();

    moveAnimationItem3_->setStartValue(ui_->pushButton_3->geometry());
    moveAnimationItem3_->setEndValue(ui_->pushButton_4->geometry());
    moveAnimationItem3_->setEasingCurve(currentEasingCurve_);
    moveAnimationItem3_->start();

    moveAnimationItem4_->setStartValue(ui_->pushButton_4->geometry());
    moveAnimationItem4_->setEndValue(ui_->pushButton->geometry());
    moveAnimationItem4_->setEasingCurve(currentEasingCurve_);
    moveAnimationItem4_->start();
}

void MainWindow::changeButtonColor() {
    generateColorAimation(colorAnimation1_);
    generateColorAimation(colorAnimation2_);
    generateColorAimation(colorAnimation3_);
    generateColorAimation(colorAnimation4_);
}

void MainWindow::generateColorAimation(QPropertyAnimation *colorAnimation) {
    int rgbMax = 255;
    int  r1 = rand() % rgbMax;
    int  g1 = rand() % rgbMax;
    int  b1 = rand() % rgbMax;

    colorAnimation->setEndValue(QColor(r1, g1, b1));
    colorAnimation->setDuration(2000);
    colorAnimation->setEasingCurve(currentEasingCurve_);
    colorAnimation->start();
}

void MainWindow::on_comboBox_activated(int index)
{
    if(index == 0) {
        currentEasingCurve_ = QEasingCurve::Linear;
    } else
        if(index == 1) {
            currentEasingCurve_ = QEasingCurve::OutQuad;
    } else
        if(index == 2) {
            currentEasingCurve_ = QEasingCurve::InElastic;
    }
    chart_->removeAllSeries();
    chart_->addSeries(generateSeries());
}

QSplineSeries* MainWindow::generateSeries() {
    QSplineSeries *series = new QSplineSeries();
    qreal threshold = 1.0f;
    qreal step = 0.05f;
    qreal i = 0.0f;
    qreal c4 = (2 * M_PI) / 3;

    if(currentEasingCurve_ == QEasingCurve::InElastic) {
        while (i <= threshold) {
            *series << QPointF(i, pow(2, 10 * i - 10) * sin((i * 10 - 10.75) * c4));
            i += step;
        }
    } else
        if(currentEasingCurve_ == QEasingCurve::Linear) {
            while (i <= threshold) {
                *series << QPointF(i, i);
                i += step;
            }
        } else
            if(currentEasingCurve_ == QEasingCurve::OutQuad) {
                while (i <= threshold) {
                    *series << QPointF(i, 1 - (1 - i) * (1 - i));
                    i += step;
                }
            }
        return series;
}
