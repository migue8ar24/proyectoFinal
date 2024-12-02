#ifndef NERD_H
#define NERD_H

#include "Personaje.h"
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Nerd : public Personaje, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Nerd(QGraphicsItem * parent=0);
    void onDeath() override;
    QTimer * timer;
    int sprite;
    float t;
public slots:
    bool move();
};

#endif //NERD_H
