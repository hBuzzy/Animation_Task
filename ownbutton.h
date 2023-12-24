#ifndef OWNBUTTON_H
#define OWNBUTTON_H

#include <QPushButton>

class OwnButton : public QPushButton {
    Q_OBJECT

    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged FINAL)

public:
    OwnButton(QWidget *parent = nullptr);
    QColor getColor() const;
    void setColor(const QColor &newColor);

signals:
    void colorChanged();

private:
    QColor color_;
};

#endif // OWNBUTTON_H
