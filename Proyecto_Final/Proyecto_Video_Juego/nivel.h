#ifndef NIVEL_H
#define NIVEL_H
#include <QString>

class Nivel
{
public:
    Nivel(const QString mapa, const QString& pista);
    QString mapa;
    QString pista;
    void iniciar();    // Método para iniciar el nivel
    void actualizar(); // Método para actualizar el nivel
    void terminar();
};

#endif // NIVEL_H
