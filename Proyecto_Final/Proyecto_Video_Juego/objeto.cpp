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
Objeto::~Objeto() { //Destructor

}
void Objeto::aplicarFuerza(QPointF _fuerza)
{
    if (masa != 0) {
        aceleracion += QPointF(_fuerza.x() / masa, _fuerza.y() / masa);
        velocidad += aceleracion*0.5;
    } else {
        aceleracion = QPointF(0, 0);
    }
}

void Objeto::actualizarMovimiento(float _deltaTiempo)
{

    float k = 0.5;
    if (abs(aceleracion.x())<=0.001 && abs(aceleracion.y())<=0.001){
        aceleracion = QPointF(0,0);
        velocidad *= 0.95;
        return;
    }
    float magnitud = sqrt(velocidad.x()*velocidad.x()+velocidad.y()*velocidad.y());
    aceleracion += -aceleracion*exp(_deltaTiempo*(-1/k))*magnitud*0.01;
    velocidad += aceleracion*_deltaTiempo; //v = v0 + a * deltaTiempo
    posicion += velocidad*_deltaTiempo; //x = x0 + v * deltaTiempo

    setPos(posicion);
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
