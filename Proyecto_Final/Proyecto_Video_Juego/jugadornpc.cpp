#include "jugadornpc.h"

jugadorNPC::jugadorNPC(QPointF _posicion, QString ruta, QPointF reescalado, qfloat16 _masa,QList<QPointF> _rutaNivel )
    : Objeto(_posicion, ruta, reescalado, _masa){
    RutaNivel = _rutaNivel;
    PosicionRuta = 0;
}

jugadorNPC::~jugadorNPC() {}

void jugadorNPC::siguientePunto()
{
    PosicionRuta += 1;
    PosicionRuta %= RutaNivel.length();
}
