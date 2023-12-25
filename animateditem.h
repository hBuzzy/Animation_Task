#ifndef ANIMATEDITEM_H
#define ANIMATEDITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPropertyAnimation>
#include <QEasingCurve>

class AnimatedItem : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    AnimatedItem();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    Q_PROPERTY(qreal value READ getValue WRITE setValue NOTIFY valueChanged)

public slots:
    void startAnimation();
    void setEasingFunction(int type);
    void curvePreviewChanged(int index);

    void setValue(qreal value);

private:
    qreal value_;
    QPropertyAnimation *animation_;
    QEasingCurve::Type currentEasingType_;
    int currentCurveIndex_ = 1;

    qreal getValue() const;

signals:
    void valueChanged(qreal value);
};

#endif // ANIMATEDITEM_H
