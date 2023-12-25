#include "mainwindow.h"
#include "animateditem.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    scene_ = new QGraphicsScene(this);
    animatedItem_ = new AnimatedItem();
    scene_->addItem(animatedItem_);

    QGraphicsView *view = new QGraphicsView(scene_);
    setCentralWidget(view);

    QComboBox *easingComboBox = new QComboBox(this);
    easingComboBox->addItem("Linear");
    easingComboBox->addItem("EaseInSine");
    easingComboBox->addItem("EaseOutSine");
    easingComboBox->addItem("EaseInOutSine");
    connect(easingComboBox, QOverload<int>::of(&QComboBox::activated), animatedItem_, &AnimatedItem::setEasingFunction);

    curveComboBox_ = new QComboBox(this);
    curveComboBox_->addItem("Синусоида");
    curveComboBox_->addItem("Косинусоида");
    curveComboBox_->addItem("Кубическая функция");
    curveComboBox_->addItem("Экспоненциальная функция");
    connect(curveComboBox_, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::curvePreviewChanged);

    QPushButton *animateButton = new QPushButton("Анимировать", this);
    connect(animateButton, &QPushButton::clicked, animatedItem_, &AnimatedItem::startAnimation);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(easingComboBox);
    layout->addWidget(curveComboBox_);
    layout->addWidget(animateButton);
    layout->addWidget(view);

    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    setCentralWidget(widget);

    connect(animatedItem_, &AnimatedItem::valueChanged, this, &MainWindow::updateStatusBar);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::curvePreviewChanged(int index) {
    animatedItem_->curvePreviewChanged(index);
}

void MainWindow::updateStatusBar(qreal value) {
    statusBar()->showMessage("Value: " + QString::number(value));
}
