#include "Alcalde.h"
#include <QGraphicsItem>
#include <Nerd.h>
#include <QDebug>
#include <Qtimer>
#include <Lvl1.h>

Alcalde::Alcalde(QGraphicsItem *parent): Personaje(1,parent){
    QPixmap pixmap(":/spritesM/sprites/SpAlcalde.png"); //sprite alcalde
    QPixmap scaledPixmap = pixmap.scaled(80, 700);
    setPixmap(scaledPixmap);

}

void Alcalde::onDeath(){
    if (scene()) {

    }
    delete this;
}

void Alcalde::colision(){

    QGraphicsItem* collidingObject = this->touch();

    if (collidingObject != nullptr) {
        if (Nerd* nerdo = dynamic_cast<Nerd*>(collidingObject)) {
            if (nerdo->scene() == scene()) {
                this->recibirDano(1);
                qDebug()<<this->getVida();
                delete nerdo;
            }
        }
    }
}

QGraphicsItem* Alcalde::touch() {
    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    for (QGraphicsItem* item : collidingItemsList) {
        if (Nerd* nerdo = dynamic_cast<Nerd*>(item)) {
            return dynamic_cast<QGraphicsItem*>(nerdo);
        }
    }
    return nullptr;
}

QList<QGraphicsItem*> Alcalde::collidingCharacters() const {
    return QGraphicsPixmapItem::collidingItems();
}
