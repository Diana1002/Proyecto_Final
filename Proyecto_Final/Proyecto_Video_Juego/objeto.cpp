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
Objeto::~Objeto()
{

}
void Objeto::aplicarFuerza(QPointF _fuerza)
{
    if (masa != 0) {
        aceleracion += QPointF(_fuerza.x() / masa, _fuerza.y() / masa);
        velocidad += aceleracion;
    } else {
        aceleracion = QPointF(0, 0);
    }
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

void Objeto::setAceleracion(QPointF _nuevaAceleracion)
{
    aceleracion=_nuevaAceleracion;
}

void Objeto::setVelocidad(QPointF _nuevaVelocidad)
{
    velocidad = _nuevaVelocidad;
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
    // Calcular la nueva posición sumando el cambio a la posición actual
    QPointF nuevaPos = posicion + _cambioPosicion;

    // Definir los límites de la pista (área de 900x700)
    QRectF limites(0, 0, 900, 700);

    // Verificar que la nueva posición esté dentro de los límites
    if (limites.contains(nuevaPos)) {
        // Si la nueva posición está dentro de los límites, actualizamos la posición
        posicion = nuevaPos;
    } else {
        // Si la nueva posición está fuera de los límites, ajustar la posición al borde más cercano
        posicion.setX(qMax(limites.left(), qMin(nuevaPos.x(), limites.right())));
        posicion.setY(qMax(limites.top(), qMin(nuevaPos.y(), limites.bottom())));
    }

    // Aplicar la nueva posición al objeto en la escena
    setPos(posicion);
}

