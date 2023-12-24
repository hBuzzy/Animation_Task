#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow) {
    ui_->setupUi(this);

   connect(ui_->animationButton, &QPushButton::clicked, this, &MainWindow::moveItems);
   connect(ui_->animationButton, &QPushButton::clicked, this, &MainWindow::changeButtonColor);
}

MainWindow::~MainWindow() {
    delete ui_;
}

void MainWindow::moveItems() {
    QPropertyAnimation *moveAnimationItem1_ = new QPropertyAnimation(ui_->pushButton, "geometry");
    moveAnimationItem1_->setDuration(2000);
    QPropertyAnimation *moveAnimationItem2_ = new QPropertyAnimation(ui_->pushButton_2, "geometry");
    moveAnimationItem2_->setDuration(2000);
    QPropertyAnimation *moveAnimationItem3_ = new QPropertyAnimation(ui_->pushButton_3, "geometry");
    moveAnimationItem3_->setDuration(2000);
    QPropertyAnimation *moveAnimationItem4_ = new QPropertyAnimation(ui_->pushButton_4, "geometry");
    moveAnimationItem4_->setDuration(2000);


    moveAnimationItem1_->setStartValue(ui_->pushButton->geometry());
    moveAnimationItem1_->setEndValue(ui_->pushButton_2->geometry());
    moveAnimationItem1_->setEasingCurve(QEasingCurve::Type::Linear);
    moveAnimationItem1_->start();

    moveAnimationItem2_->setStartValue(ui_->pushButton_2->geometry());
    moveAnimationItem2_->setEndValue(ui_->pushButton_3->geometry());
    moveAnimationItem2_->setEasingCurve(QEasingCurve::Type::InSine);
    moveAnimationItem2_->start();

    moveAnimationItem3_->setStartValue(ui_->pushButton_3->geometry());
    moveAnimationItem3_->setEndValue(ui_->pushButton_4->geometry());
    moveAnimationItem3_->setEasingCurve(QEasingCurve::Type::OutQuad );
    moveAnimationItem3_->start();

    moveAnimationItem4_->setStartValue(ui_->pushButton_4->geometry());
    moveAnimationItem4_->setEndValue(ui_->pushButton->geometry());
    moveAnimationItem4_->setEasingCurve(QEasingCurve::Type::InOutElastic);
    moveAnimationItem4_->start();
}

void MainWindow::changeButtonColor() {
      int  r1 = rand() %255;
      int  g1 = rand() %255;
      int  b1 = rand() %255;

      QPropertyAnimation *colorAnimation = new QPropertyAnimation(ui_->pushButton, "color");
      colorAnimation->setEndValue(QColor(r1, g1, b1));
      colorAnimation->setDuration(2000);
      colorAnimation->setEasingCurve(QEasingCurve::Linear);
      colorAnimation->start();

      int  r2 = rand() %255;
      int  g2 = rand() %255;
      int  b2 = rand() %255;

      QPropertyAnimation *colorAnimation_2 = new QPropertyAnimation(ui_->pushButton_2, "color");
      colorAnimation_2->setEndValue(QColor(r2, g2, b2));
      colorAnimation_2->setDuration(2000);
      colorAnimation_2->setEasingCurve(QEasingCurve::InSine);
      colorAnimation_2->start();

      int  r3 = rand() %255;
      int  g3 = rand() %255;
      int  b3 = rand() %255;

      QPropertyAnimation *colorAnimation_3 = new QPropertyAnimation(ui_->pushButton_3, "color");
      colorAnimation_3->setEndValue(QColor(r3, g3, b3));
      colorAnimation_3->setDuration(2000);
      colorAnimation_3->setEasingCurve(QEasingCurve::OutQuad);
      colorAnimation_3->start();

      int  r4 = rand() %255;
      int  g4 = rand() %255;
      int  b4 = rand() %255;

      QPropertyAnimation *colorAnimation_4 = new QPropertyAnimation(ui_->pushButton_4, "color");
      colorAnimation_4->setEndValue(QColor(r4, g4, b4));
      colorAnimation_4->setDuration(2000);
      colorAnimation_4->setEasingCurve(QEasingCurve::InOutElastic);
      colorAnimation_4->start();

}


