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

Homero::Homero(QGraphicsItem *parent): Personaje(100, parent){
    QPixmap pixmap(":/spritesM/sprites/SpHomeroC1.png");
    QPixmap scaledPixmap = pixmap.scaled(80, 80);
    setPixmap(scaledPixmap);

}



void Homero::recargarHabilidad() {
    int radioBate = this->getCarga();

    shared_ptr<Arma> bateAtaque=this->getArma();
    if (shared_ptr<BateDeBeisbol> bate = dynamic_pointer_cast<BateDeBeisbol>(bateAtaque)) {
        radioBate+=1;
        this->setCarga(radioBate);

    }

}

int Homero::getCarga(){
    return cargaEspecial;
}
void Homero::setCarga(int _cargaEspecial){
    cargaEspecial = _cargaEspecial;

}

void Homero::keyPressEvent(QKeyEvent *event)
{
    qreal xPos = x();
    qreal yPos = y();
    QPointF newPos = pos();

    if (event -> key() == Qt::Key_A){
        if (xPos - 7 >= 0){
            newPos.setX(xPos -7);
        }
    }
    if (event -> key() == Qt::Key_D){
        if (xPos + (7+80) <= 1550){
            newPos.setX(xPos +7);
        }
    }
    if (event -> key() == Qt::Key_W){
        if (yPos - (7) >= 0){
            newPos.setY(yPos -7);
        }
    }
    if (event -> key() == Qt::Key_S){
        if (yPos + (7 + 80) <= 780){
            newPos.setY(yPos +7);
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
                    if (nerdo->getVida() <= 0 ){ nerdo->onDeath(); }
                }
            }
            if (BateDeBeisbol* bate = dynamic_cast<BateDeBeisbol*>(collidingObject)) {
                if (bate->scene() == scene()) {
                    scene()->removeItem(bate);
                    shared_ptr<BateDeBeisbol> bate = make_shared<BateDeBeisbol>();
                    this->Personaje::equiparArma(bate);
                    this->changeTexture(":/spritesM/sprites/SpPixHomBat.png");
                }
            }
        }
    }
    else if (event -> key() == Qt::Key_E){
        shared_ptr<Arma> bateAtaque=this->getArma();
        if (shared_ptr<BateDeBeisbol> bate = dynamic_pointer_cast<BateDeBeisbol>(bateAtaque)) {
            bate->BateDeBeisbol::ataqueCircular(scene(), this->getCarga(),xPos,yPos);
            this->setCarga(0);

        }
    }
    setPos(newPos);
}

void Homero::spawnNerd(){
    Nerd * nerdo = new Nerd();
    scene()->addItem(nerdo);
}

void Homero::onDeath() {
    if (scene()) {
        scene()->removeItem(this);
    }
    delete this;
}


void Homero::changeTexture(const QString& rutaSprite) {
    QPixmap newPixmap(rutaSprite);
    QPixmap scaledPixmap = newPixmap.scaled(80, 80);
    setPixmap(scaledPixmap);
}
