#ifndef JUGADORREAL_H
#define JUGADORREAL_H
#include "objeto.h"

class jugadorReal : public Objeto
{
public:
    jugadorReal(QPointF _posicion, QString ruta, QPointF reescalado, qfloat16 _masa);
    ~jugadorReal();
};

#endif // JUGADORREAL_H
