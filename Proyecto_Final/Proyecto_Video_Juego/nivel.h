#ifndef NIVEL_H
#define NIVEL_H

#include <QGraphicsItem>
#include <QPainter>

class Nivel : public QGraphicsItem {
public:
    Nivel(QPointF center, int outerWidth, int outerHeight, int innerWidth, int innerHeight);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    QPointF center;
    int outerWidth;
    int outerHeight;
    int innerWidth;
    int innerHeight;
};

#endif // NIVEL_H

