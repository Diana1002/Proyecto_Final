#include "objeto.h"


Objeto::Objeto(QPoint _posicion, QString ruta, QPointF reescalado)
{
    posicion=_posicion;
    // Cargar imagen
    QPixmap imagenObjeto(ruta);
    if (imagenObjeto.isNull()){
        qDebug() << "No se pudo cargar la imagen";
        return;
    }
    QPixmap scaledImagen = imagenObjeto.scaled(imagenObjeto.width() * reescalado.x(), imagenObjeto.height() * reescalado.y(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imagenItem = new QGraphicsPixmapItem(scaledImagen);
}

void Objeto::mover()
{

}
