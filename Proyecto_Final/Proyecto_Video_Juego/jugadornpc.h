#ifndef JUGADORNPC_H
#define JUGADORNPC_H
#include "objeto.h"

class jugadorNPC : public Objeto
{
public:
    jugadorNPC(QPointF _posicion, QString ruta, QPointF reescalado, qfloat16 _masa);
    ~jugadorNPC();
};

#endif // JUGADORNPC_H
