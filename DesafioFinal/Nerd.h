#ifndef NERD_H
#define NERD_H

#include "Personaje.h"
#include <QGraphicsRectItem>
#include <QObject>

class Nerd : public Personaje {
    Q_OBJECT
public:
    Nerd(QGraphicsItem * parent=0);
    void atacar(Personaje& objetivo) override;
    float t;
public slots:
    void move();
};

#endif // NERD_H
