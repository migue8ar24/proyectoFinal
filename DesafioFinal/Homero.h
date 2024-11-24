#ifndef HOMERO_H
#define HOMERO_H

#include "Personaje.h"
#include "QGraphicsRectItem"
#include "QTimer"
#include <map>


class Homero : public Personaje {
    Q_OBJECT

private:
    int cargaEspecial; // Carga de la habilidad especial

public:
    Homero(QGraphicsItem * parent=0);
    void atacar(Personaje& objetivo);
    void usarHabilidadEspecial();
    void recargarHabilidad(); // Recarga de habilidad con el tiempo
    void keyPressEvent(QKeyEvent *event);


public slots:
    void spawnNerd();
};

#endif // HOMERO_H
