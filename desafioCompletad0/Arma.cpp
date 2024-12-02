#include <Arma.h>
#include "Nerd.h"

using namespace std;

Arma::Arma(int dano, int alcance)
    :dano(dano), alcance(alcance){}

//getters
int Arma::getDano() {return dano;}
int Arma::getAlcance(){return alcance;}

QGraphicsItem* Arma::touch() {
    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    for (QGraphicsItem* item : collidingItemsList) {
        if (Nerd* nerdo = dynamic_cast<Nerd*>(item)) {
            return dynamic_cast<QGraphicsItem*>(nerdo);
        }
        else if (BateDeBeisbol* bate = dynamic_cast<BateDeBeisbol*>(item)) {
            return dynamic_cast<QGraphicsItem*>(bate);
        }
    }
    return nullptr;
}
