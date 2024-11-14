#include "objeto.h"


Objeto::Objeto(QPointF _posicion, QString ruta, QPointF reescalado, qfloat16 _masa)
{
    posicion=_posicion;
    masa = _masa;
    //Cargar imagen desde la ruta
    QPixmap imagenObjeto(ruta);
    if (imagenObjeto.isNull()){
        qDebug() << "No se pudo cargar la imagen";
        return;
    }
    //Escalar imagen
    QPixmap scaledImagen = imagenObjeto.scaled(imagenObjeto.width() * reescalado.x(), imagenObjeto.height() * reescalado.y(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //Crear el grafico y posicionarlo
    imagenItem = new QGraphicsPixmapItem(scaledImagen);
    imagenItem->setPos(posicion);
}
Objeto::~Objeto() { //Destructor
    delete imagenItem;
}

QPointF Objeto::getPosicion() const
{
    return posicion;
}

QPointF Objeto::getVelocidad() const
{
    return velocidad;
}

QPointF Objeto::getAceleracion() const
{
    return aceleracion;
}

void Objeto::mover(QPointF _cambioPosicion)
{
    posicion+=_cambioPosicion;
    imagenItem->setPos(posicion);
}

void Objeto::aplicarFuerza(QPointF _fuerza)
{

    if (masa != 0) {
        aceleracion = QPointF(_fuerza.x() / masa, _fuerza.y() / masa);
    } else {
        aceleracion = QPointF(0, 0);
    }
}

void Objeto::actualizarMovimiento(float _deltaTiempo)
{
    velocidad += aceleracion*_deltaTiempo; //v = v0 + a * deltaTiempo
    posicion += velocidad*_deltaTiempo; //x = x0 + v * deltaTiempo
    if (imagenItem) {
        imagenItem->setPos(posicion);
    }
    aceleracion *= 0.95;
}
