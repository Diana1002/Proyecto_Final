#include "nivel.h"
#include <QDebug>

Nivel::Nivel(int nivel, int vidasIniciales)
    : nivelActual(nivel), vidas(vidasIniciales) {
    scene = new QGraphicsScene();
    fondoPista = nullptr;
}

void Nivel::iniciar(const QString &rutaImagen)
{
    qDebug() << "Iniciando nivel" << nivelActual << "con" << vidas << "vidas.";

    // Cargar la pista
    QPixmap pixmap(rutaImagen);
    if (pixmap.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen de la pista:" << rutaImagen;
        return;
    }

    fondoPista = new QGraphicsPixmapItem(pixmap);
    scene->addItem(fondoPista);       // Agregar la imagen a la escena
    fondoPista->setZValue(-1);        // Asegurar que la imagen está en el fondo
    scene->setSceneRect(0, 0, pixmap.width(), pixmap.height());

    qDebug() << "Pista cargada con éxito.";
}



void Nivel::terminar()
{

}

QGraphicsScene* Nivel::getScene() const{
    return scene;
}
// Reducir vidas
void Nivel::reducirVida() {
    if (vidas > 0) {
       /// vidas--;
        qDebug() << "Vida perdida. Vidas restantes:" << vidas;

        if (vidas == 0) {
            qDebug() << "Juego terminado. Has perdido todas las vidas.";
        }
    }
}

// Obtener el número de vidas restantes
int Nivel::getVidas() const {
    return vidas;
}
