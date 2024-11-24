#include <Arma.h>
#include <string>
#include "QGraphicsRectItem"
#include "QGraphicsScene"
#include <QApplication>
#include <QGraphicsView>
#include <QKeyEvent>
#include "QTimer"

#include "puno.h"
#include "Nerd.h"
#include "BateDeBeisbol.h"
using namespace std;

Arma::Arma(const string &nombre, int dano, int alcance)
    :nombre(nombre), dano(dano), alcance(alcance){}

//getters
int Arma::getDano() {return dano;}
int Arma::getAlcance(){return alcance;}
string Arma::getNombre(){return nombre;}


QGraphicsItem* Arma::touch() {
    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    for (QGraphicsItem* item : collidingItemsList) {
        if (Nerd* nerdo = dynamic_cast<Nerd*>(item)) {
            return dynamic_cast<QGraphicsItem*>(nerdo);
        }
        else if (BateDeBeisbol * bate = dynamic_cast<BateDeBeisbol*>(item)) {
            return dynamic_cast<QGraphicsItem*>(bate);
        }
    }
    return nullptr;
}


//o usar ladechatgpt

