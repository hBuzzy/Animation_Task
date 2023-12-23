#include "animateditem.h"

#include <QDebug>
#include <QPainter>
#include <qmath.h>

AnimatedItem::AnimatedItem() : QObject(), QGraphicsItem(), value_(0), currentEasingType_(QEasingCurve::Linear) {
    animation_ = new QPropertyAnimation(this, "value");
    connect(animation_, SIGNAL(valueChanged(qreal)), this, SLOT(updateValue(qreal)));
}

QRectF AnimatedItem::boundingRect() const {
    return QRectF(0, 0, 100, 100);
}

void AnimatedItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QVector<QPointF> points;
    for (int i = 0; i <= 100; ++i) {
         qreal x = i;
         qreal y = 50 + 40 * qSin(2 * M_PI * i / 100.0 * value_ / 100.0);
         points.append(QPointF(x, y));
     }

     painter->drawPolyline(points.data(), points.size());
}

void AnimatedItem::startAnimation() {
    animation_->setStartValue(0);
    animation_->setEndValue(100);
    animation_->setEasingCurve(QEasingCurve(currentEasingType_));
    animation_->setDuration(1000);
    animation_->start();
    qDebug() << "Button clicked";
}

void AnimatedItem::setEasingFunction(int type) {
    if (type >= 0 && type < QEasingCurve::NCurveTypes) {
        currentEasingType_ = static_cast<QEasingCurve::Type>(type);
        qDebug() << "Type change" << currentEasingType_;
    }
}

void AnimatedItem::updateValue(qreal value) {
    setValue(value);
}

qreal AnimatedItem::getValue() const {
    return value_;
}

void AnimatedItem::setValue(qreal value) {
    if (value != value_) {
        value_ = value;
        emit valueChanged(value_);
        qDebug() << "Value update" << value_;
        update();
    }
}
