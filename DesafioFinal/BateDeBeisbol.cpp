#include "BateDeBeisbol.h"
#include "QGraphicsScene"
#include "QGraphicsItem"
#include "QGraphicsRectItem"
#include "QGraphicsEllipseItem"
#include "QDebug"
#include <QTimer>

#include "Nerd.h"


BateDeBeisbol::BateDeBeisbol(QGraphicsItem *parent): Arma("bate", 20, 20),QGraphicsEllipseItem(parent){
    setRect(0,0,20,20);
}

QList<QGraphicsItem*> BateDeBeisbol::collidingItems() const {
    return QGraphicsEllipseItem::collidingItems();
}

void BateDeBeisbol::ataqueCircular(QGraphicsScene* escena, int radio,int _xPos,int _yPos){
    setRect(0,0,radio *10,radio *10);
    setPos(_xPos -((radio*5)-20),_yPos-((radio*5)-20));
    escena->addItem(this);
    hit();
    QTimer::singleShot(500, this, &BateDeBeisbol::borrarBate);
}

void BateDeBeisbol::hit(){



    QGraphicsItem* collidingObject = touch();

    if (collidingObject != nullptr) {
        if (Nerd* nerdo = dynamic_cast<Nerd*>(collidingObject)) {
            if (nerdo->scene() == scene()) {
                nerdo->recibirDano(20);
            }
        }
    }
}



void BateDeBeisbol::borrarBate(){
    BateDeBeisbol::scene()->removeItem(this);
}


