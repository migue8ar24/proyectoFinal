#ifndef HOMERO_H
#define HOMERO_H

#include "Personaje.h"
#include "QGraphicsRectItem"
#include "QTimer"
#include <map>
#include <QObject>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <map>



class Homero : public Personaje, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    int cargaEspecial = 0;

public:
    Homero(QGraphicsItem * parent=0);
    void usarHabilidadEspecial();
    void changeTexture(const QString& rutaSprite);
    void keyPressEvent(QKeyEvent *event);
    int getCarga();
    void setCarga(int cargaEspecial);
    void onDeath() override;

public slots:
    void spawnNerd();
    void recargarHabilidad();
};

#endif // HOMERO_H
