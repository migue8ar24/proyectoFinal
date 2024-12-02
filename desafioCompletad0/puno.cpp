#include "puno.h"
#include "QGraphicsRectItem"
#include "QGraphicsScene"
#include "Nerd.h"
#include "QTimer"
#include "BateDeBeisbol.h"

Puno::Puno(QGraphicsItem *parent): Arma(2,0){

    //setRect(0,0,40,20);

    QPixmap pixmap(":/spritesM/sprites/SpHomerFist.png");
    QPixmap scaledPixmap = pixmap.scaled(60, 40);
    setPixmap(scaledPixmap);

    timerGolpe = new QTimer(this);
    connect(timerGolpe, &QTimer::timeout, this, &Puno::borrarGolpe);
    timerGolpe->start(500);

}

void Puno::borrarGolpe(){
    Puno::scene()->removeItem(this);
    delete this;
}

QList<QGraphicsItem*> Puno::collidingItems() const {
    return QGraphicsPixmapItem::collidingItems();
}
