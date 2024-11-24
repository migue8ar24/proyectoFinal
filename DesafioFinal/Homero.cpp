#include "Homero.h"
#include "Nerd.h"
#include "puno.h"
#include "BateDeBeisbol.h"
#include "Personaje.h"


#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>

Homero::Homero(QGraphicsItem *parent): Personaje(parent){
    this->setRect(0,0,50,50);
}

void Homero::atacar(Personaje& objetivo) {}
void Homero::recargarHabilidad() {}

void Homero::keyPressEvent(QKeyEvent *event)
{
    qreal xPos = x();
    qreal yPos = y();
    QPointF newPos = pos();

    if (event -> key() == Qt::Key_A){
        if (xPos - 5 >= 0){
            newPos.setX(xPos -5);
        }
    }
    if (event -> key() == Qt::Key_D){
        if (xPos + (5+100) <= 1550){
            newPos.setX(xPos +5);
        }
    }
     if (event -> key() == Qt::Key_W){
        if (yPos - (5) >= 0){
            newPos.setY(yPos -5);
        }
    }
    if (event -> key() == Qt::Key_S){
        if (yPos + (5 + 100) <= 780){
            newPos.setY(yPos +5);
        }
    }
    else if (event -> key() == Qt::Key_Space){
        Puno * puno = new Puno();
        puno -> setPos(x()-40,y());
        scene() -> addItem(puno);

        QGraphicsItem* collidingObject = puno->touch();

        if (collidingObject != nullptr) {
            if (Nerd* nerdo = dynamic_cast<Nerd*>(collidingObject)) {
                if (nerdo->scene() == scene()) {
                    nerdo->Personaje::recibirDano(2);
                    nerdo->setPos(x()-105,y());
                }
            }
            if (BateDeBeisbol* bate = dynamic_cast<BateDeBeisbol*>(collidingObject)) {
                if (bate->scene() == scene()) {
                    scene()->removeItem(bate);
                    shared_ptr<BateDeBeisbol> bate = make_shared<BateDeBeisbol>();
                    this->Personaje::equiparArma(bate);
                    //cambiar sprite?
                }
            }
        }
    }
    else if (event -> key() == Qt::Key_E){
        shared_ptr<Arma> bateAtaque=this->getArma();
        if (shared_ptr<BateDeBeisbol> bate = dynamic_pointer_cast<BateDeBeisbol>(bateAtaque)) {
            bate->BateDeBeisbol::ataqueCircular(scene(), 20,xPos,yPos); //añadir radio dependiendo de carga
        }
    }
    setPos(newPos);
}

void Homero::spawnNerd(){
    Nerd * nerdo = new Nerd();
    scene()->addItem(nerdo);
}


