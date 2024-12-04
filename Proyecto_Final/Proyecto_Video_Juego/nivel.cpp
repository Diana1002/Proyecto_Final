#include "nivel.h"

Nivel::Nivel(QPointF center, int outerWidth, int outerHeight, int innerWidth, int innerHeight)
    : center(center), outerWidth(outerWidth), outerHeight(outerHeight),
    innerWidth(innerWidth), innerHeight(innerHeight) {}

QRectF Nivel::boundingRect() const {
    // Definimos el rectángulo de contorno que cubre la pista exterior
    return QRectF(center.x() - outerWidth, center.y() - outerHeight,
                  outerWidth * 2, outerHeight * 2);
}

void Nivel::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Habilitar antialiasing para suavizar bordes
    painter->setRenderHint(QPainter::Antialiasing);

    // Ajustar el tamaño de las elipses para que ocupen más espacio en la ventana
    int outerWidth = 400; // Ancho de la elipse exterior
    int outerHeight = 300; // Alto de la elipse exterior
    int innerWidth = 300;  // Ancho de la elipse interior
    int innerHeight = 200; // Alto de la elipse interior

    // Definir el centro de la pista (centro de la ventana)
    QPointF center(0, 0); // Centro de la ventana (900x700)

    // Dibujar el área entre las dos elipses como blanco
    QBrush brush(Qt::black); // Relleno blanco
    painter->setBrush(brush);
    painter->setPen(Qt::NoPen); // Sin borde
    painter->drawEllipse(center, outerWidth, outerHeight); // Elipse exterior

    // Rellenar el interior de la pista con el fondo verde
    painter->setBrush(QBrush(Qt::green)); // Fondo verde para la pista
    painter->drawEllipse(center, innerWidth, innerHeight); // Elipse interior

    // Opcional: Dibujar bordes blancos para las dos elipses
    QPen pen(Qt::white, 2); // Bordes blancos
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);

    // Bordes de la pista exterior
    painter->drawEllipse(center, outerWidth, outerHeight);

    // Bordes de la pista interior
    painter->drawEllipse(center, innerWidth, innerHeight);
}
