#include "mainwindow.h"
#include "animateditem.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QComboBox>
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
    connect(easingComboBox, SIGNAL(activated(int)), animatedItem_, SLOT(setEasingFunction(int)));

    QPushButton *animateButton = new QPushButton("Анимировать", this);
    connect(animateButton, SIGNAL(clicked()), animatedItem_, SLOT(startAnimation()));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(easingComboBox);
    layout->addWidget(animateButton);
    layout->addWidget(view);

    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    setCentralWidget(widget);

    connect(animatedItem_, SIGNAL(valueChanged(qreal)), this, SLOT(updateStatusBar(qreal)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateStatusBar(qreal value) {
    statusBar()->showMessage("Value: " + QString::number(value));
}
