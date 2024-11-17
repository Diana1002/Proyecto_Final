#ifndef OBJETO_H
#define OBJETO_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <cmath>

class Objeto : public QGraphicsItem
{
public:
    //Constructor
    Objeto(QPointF _posicion, QString ruta, QPointF reescalado=QPointF(1,1), float _masa = 1 );
    //Destructor
    ~Objeto();
    QPointF posicion;
    QPixmap imagen;
    void mover(QPointF _cambioPosicion);
    void aplicarFuerza(QPointF _fuerza);   // Aplicar fuerza al objeto
    void actualizarMovimiento(float _deltaTiempo);
    float masa;
    void setVelocidad(QPointF _nuevaVelocidad);
    QPointF getPosicion() const;
    QPointF getVelocidad() const;
    QPointF getAceleracion() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPointF velocidad;
    QPointF aceleracion;
    float deltaTiempo;

};

#endif // OBJETO_H
