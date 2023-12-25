#include "animateditem.h"

#include <QDebug>
#include <QPainter>
#include <qmath.h>

AnimatedItem::AnimatedItem() : QObject(), QGraphicsItem(), value_(0), currentEasingType_(QEasingCurve::Linear) {
    animation_ = new QPropertyAnimation(this, "value");
    connect(animation_, &QPropertyAnimation::valueChanged, this, [this](const QVariant &value) {
        if (value.canConvert<qreal>()) {
            setValue(value.value<qreal>());
        }
    });
}

QRectF AnimatedItem::boundingRect() const {
    return QRectF(0, 0, 250, 200);
}

void AnimatedItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    const int pointCount = 200;
    const qreal kScaleFactor = 40.0;
    const qreal kXOffset = 50.0;
    const qreal kYOffset = 50.0;

    QVector<QPointF> points;
    for (int i = 0; i <= pointCount; ++i) {
        qreal x = i + kXOffset;
        qreal y = kYOffset;

        switch (currentCurveIndex_) {
            case 0:
                y += kScaleFactor * qSin(2 * M_PI * i / pointCount * value_ / 100.0);
                break;
            case 1:
                y += kScaleFactor * qCos(2 * M_PI * i / pointCount * value_ / 100.0);
                break;
            case 2:
                y += kScaleFactor * qPow(i / qreal(pointCount), 3) * value_ / 100.0;
                break;
            case 3:
                y += kScaleFactor * qExp(i / qreal(pointCount) * value_ / 100.0);
                break;
        }

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
}

void AnimatedItem::setEasingFunction(int type) {
    if (type >= 0 && type < QEasingCurve::NCurveTypes) {
        currentEasingType_ = static_cast<QEasingCurve::Type>(type);
    }
}

qreal AnimatedItem::getValue() const {
    return value_;
}

void AnimatedItem::setValue(qreal value) {
    if (value != value_) {
        value_ = value;
        emit valueChanged(value_);
        update();
    }
}

void AnimatedItem::curvePreviewChanged(int index) {
    currentCurveIndex_ = index;
}
