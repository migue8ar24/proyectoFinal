#ifndef ALCALDE_H
#define ALCALDE_H

#include "Personaje.h"
#include <QGraphicsPixmapItem>
#include <QObject>


class Alcalde : public Personaje, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Alcalde(QGraphicsItem * parent=0);
    void onDeath() override;
    QGraphicsItem* touch();
    QList<QGraphicsItem*> collidingCharacters() const;


public slots:
    void colision();
};

#endif // ALCALDE_H
