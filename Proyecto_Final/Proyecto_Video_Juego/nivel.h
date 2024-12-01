#ifndef NIVEL_H
#define NIVEL_H
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class Nivel
{
public:
    QGraphicsScene*scene;
    QGraphicsPixmapItem* fondoPista;
    Nivel(int nivel, int vidasIniciales);
    int vidas;
    int nivelActual;
    void iniciar(const QString &rutaImagen);    // Método para iniciar el nivel
    void terminar();
    int getVidas() const;
    //void cargarPista(const QString& rutaImagen);
    QGraphicsScene* getScene() const;

    void reducirVida();
};


#endif // NIVEL_H
