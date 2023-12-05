#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

#include "ui_MainWindow.h"
#include "easing_function.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
        ui->setupUi(this);
        for (auto&& type : EasingFunction::GetSupportedTypes()) {
            auto* easingFunction = new EasingFunction(
                std::forward<decltype(type)>(type));
            ui->easingList->addItem(easingFunction);
            ui->easingList->setItemWidget(easingFunction, easingFunction);
        }
        connect(ui->easingList, &QListWidget::currentItemChanged,
            ui->animatedButton, &AnimatedButton::SetEasingFunction);
        ui->easingList->setCurrentRow(0);
    }
    ~MainWindow() final {
        delete ui;
    }
private:
    Ui::MainWindow* ui;
};

#endif
