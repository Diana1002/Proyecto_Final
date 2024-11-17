#include "jugadorreal.h"

jugadorReal::jugadorReal(QPointF _posicion, QString ruta, QPointF reescalado, qfloat16 _masa)
    : Objeto(_posicion, ruta, reescalado, _masa){}

jugadorReal::~jugadorReal() {}
