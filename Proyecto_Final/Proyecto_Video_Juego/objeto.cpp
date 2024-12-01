#include "objeto.h"

Objeto::Objeto(QPointF _posicion, QString ruta, QPointF reescalado, float _masa)
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
    imagen = imagenObjeto.scaled(imagenObjeto.width() * reescalado.x(), imagenObjeto.height() * reescalado.y(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPos(posicion);
}
Objeto::~Objeto() {}
void Objeto::aplicarFuerza(QPointF _fuerza)
{
    if (masa != 0) {
        aceleracion += QPointF(_fuerza.x() / masa, _fuerza.y() / masa);
        velocidad += aceleracion;
    } else {
        aceleracion = QPointF(0, 0);
    }
}

void Objeto::setAceleracion(QPointF _nuevaAceleracion)
{
    aceleracion=_nuevaAceleracion;
}

void Objeto::setVelocidad(QPointF _nuevaVelocidad)
{
    velocidad = _nuevaVelocidad;
}

QRectF Objeto::boundingRect() const {
    return QRectF(0, 0, imagen.width(), imagen.height());
}

void Objeto::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (!imagen.isNull()) {
        painter->drawPixmap(0, 0, imagen); // Dibuja la imagen en la posición (0, 0) relativa al elemento
    }
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
    setPos(posicion);
}
