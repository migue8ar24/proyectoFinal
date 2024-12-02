#include "BateDeBeisbol.h"
#include "QGraphicsScene"
#include "QGraphicsItem"
#include "QGraphicsRectItem"
#include "QGraphicsEllipseItem"
#include "QDebug"
#include <QTimer>
#include <QGraphicsPixmapItem>


#include "Nerd.h"


BateDeBeisbol::BateDeBeisbol(QGraphicsItem *parent): Arma(20, 20){
    //setRect(0,0,20,20);

    QPixmap pixmap(":/spritesM/sprites/SpBate.png");
    QPixmap scaledPixmap = pixmap.scaled(50, 50);
    setPixmap(scaledPixmap);
}

QList<QGraphicsItem*> BateDeBeisbol::collidingItems() const {
    return QGraphicsPixmapItem::collidingItems();
}

void BateDeBeisbol::ataqueCircular(QGraphicsScene* escena, int radio,int _xPos,int _yPos){

    QPixmap pixmap(":/spritesM/sprites/SpAtaqueCircular.png");
    QPixmap scaledPixmap = pixmap.scaled(radio *10,radio *10);
    setPixmap(scaledPixmap);

    setPos(_xPos -((radio*5)-20),_yPos-((radio*5)-20));
    escena->addItem(this);
    hit();
    QTimer::singleShot(200, this, &BateDeBeisbol::borrarBate);
}

void BateDeBeisbol::hit(){

    QGraphicsItem* collidingObject = touch();

    if (collidingObject != nullptr) {
        if (Nerd* nerdo = dynamic_cast<Nerd*>(collidingObject)) {
            if (nerdo->scene() == scene()) {
                nerdo->recibirDano(20);
            }
            if (nerdo->getVida() <= 0 ){ nerdo->onDeath(); }
        }
    }
}

void BateDeBeisbol::borrarBate(){
    BateDeBeisbol::scene()->removeItem(this);
}
