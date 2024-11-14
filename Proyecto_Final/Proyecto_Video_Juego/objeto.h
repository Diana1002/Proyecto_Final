#ifndef OBJETO_H
#define OBJETO_H
#include <QGraphicsItem>
#include <QDebug>

class Objeto
{
public:
    //Constructor
    Objeto(QPointF _posicion, QString ruta, QPointF reescalado=QPointF(1,1), qfloat16 _masa = 1.0F );
    //Destructor
    ~Objeto();
    QPointF posicion;
    QGraphicsItem *imagenItem=nullptr;
    void mover(QPointF _cambioPosicion);
    void aplicarFuerza(QPointF _fuerza);   // Aplicar fuerza al objeto
    void actualizarMovimiento(float _deltaTiempo);
    float masa;
    QPointF getPosicion() const;

    QPointF getVelocidad() const;

    QPointF getAceleracion() const;

private:
    QPointF velocidad;
    QPointF aceleracion;
    float deltaTiempo;
};

#endif // OBJETO_H
