#ifndef OBJETO_H
#define OBJETO_H
#include <QGraphicsItem>
#include <QDebug>

class Objeto
{
public:
    Objeto(QPoint _posicion, QString ruta, QPointF reescalado=QPointF(1,1));

    QPoint posicion;
    QGraphicsItem *imagenItem=nullptr;
};

#endif // OBJETO_H
