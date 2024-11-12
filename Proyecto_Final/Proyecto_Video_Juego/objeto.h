#ifndef OBJETO_H
#define OBJETO_H
#include <QGraphicsItem>
#include <QDebug>

class Objeto
{
public:
    Objeto(QPoint _posicion, QString ruta, QPointF reescalado=QPointF(1,1));

    QPointF posicion;
    QGraphicsItem *imagenItem=nullptr;
    void mover(QPointF _posicion);
};

#endif // OBJETO_H
