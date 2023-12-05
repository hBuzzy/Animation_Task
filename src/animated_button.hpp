#ifndef ANIMATED_BUTTON_HPP
#define ANIMATED_BUTTON_HPP

#include <QPushButton>
#include <QAnimationGroup>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

#include "easing_function.hpp"

class AnimatedButton : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(QColor color READ GetColor WRITE SetColor NOTIFY ColorChanged FINAL)
public:
    AnimatedButton(QWidget *parent = nullptr) : QPushButton(parent) {
        connect(this, &QPushButton::clicked, this, &AnimatedButton::Animate);
    }
    [[nodiscard]] QColor GetColor() const {
        return color_;
    }
    void SetColor(const QColor &newColor) {
        if (color_ == newColor)
            return;
        color_ = newColor;
        setStyleSheet(QString("background: rgb(%1, %2, %3);")
            .arg(color_.red()).arg(color_.green()).arg(color_.blue()));
        emit ColorChanged();
    }
signals:
    void ColorChanged();
public slots:
    void SetEasingFunction(QListWidgetItem* current, QListWidgetItem* previous) {
        Q_UNUSED(previous)
        easingFunction_ = dynamic_cast<EasingFunction*>(current);
    }
private slots:
    void Animate() {
        auto* moveAnimation = new QPropertyAnimation(this, "geometry");
        auto [parentWidth, parentHeight] = parentWidget()->rect().size();
        const QSize buttonSize = size();
        moveAnimation->setStartValue(QRect({0, parentHeight - height()}, buttonSize));
        moveAnimation->setKeyValues(easingFunction_->GetKeyFrames(
            [&](qreal x, qreal y) noexcept {
                return QRect({
                    static_cast<int>(x * (parentWidth - width())),
                    static_cast<int>((1 - y) * (parentHeight - height()))
                }, buttonSize);
            }
        ));
        moveAnimation->setEndValue(QRect({parentWidth - width(), 0}, buttonSize));
        moveAnimation->setDuration(kAnimationDuration_);
        moveAnimation->setEasingCurve(easingFunction_->GetType());

        auto* colorAnimation = new QPropertyAnimation(this, "color");
        colorAnimation->setStartValue(QColor(255, 255, 255));
        colorAnimation->setEndValue(QColor(50, 50, 50));
        colorAnimation->setDuration(kAnimationDuration_);
        colorAnimation->setEasingCurve(easingFunction_->GetType());

        auto* group = new QParallelAnimationGroup;
        group->addAnimation(moveAnimation);
        group->addAnimation(colorAnimation);
        group->setLoopCount(1);
        group->start();
    }
private:
    QColor color_;
    EasingFunction* easingFunction_;
    static constexpr uint kAnimationDuration_ = 2000;
};

#endif
