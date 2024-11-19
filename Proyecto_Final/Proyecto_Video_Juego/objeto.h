#ifndef OBJETO_H
#define OBJETO_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <cmath>

class Objeto : public QGraphicsItem
{

public:
    Objeto(QPointF _posicion, QString ruta, QPointF reescalado=QPointF(1,1), float _masa = 1 );
    ~Objeto();
    QPointF posicion;
    QPixmap imagen;
    QPointF getPosicion() const;
    QPointF getVelocidad() const;
    QPointF getAceleracion() const;
    QRectF boundingRect() const;
    float masa;
    void mover(QPointF _cambioPosicion);
    void aplicarFuerza(QPointF _fuerza);   // Aplicar fuerza al objeto
    void setAceleracion(QPointF _nuevaAceleracion);
    void setVelocidad(QPointF _nuevaVelocidad);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPointF velocidad;
    QPointF aceleracion;
};

#endif // OBJETO_H
