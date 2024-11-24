#include "puno.h"
#include "QGraphicsRectItem"
#include "QGraphicsScene"
#include "Nerd.h"
#include "QTimer"
#include "BateDeBeisbol.h"

Puno::Puno(QGraphicsItem *parent): Arma("puno",2,0), QGraphicsRectItem(parent){

    setRect(0,0,40,20);

    timerGolpe = new QTimer(this);
    connect(timerGolpe, &QTimer::timeout, this, &Puno::borrarGolpe);
    timerGolpe->start(500);

}

void Puno::borrarGolpe(){
    Puno::scene()->removeItem(this);
    delete this;
}

QList<QGraphicsItem*> Puno::collidingItems() const {
    return QGraphicsRectItem::collidingItems();
}
