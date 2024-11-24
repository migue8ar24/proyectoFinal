#include "Personaje.h"
#include "QGraphicsScene"
#include "QGraphicsItem"
#include "BateDeBeisbol.h"
using namespace std;

Personaje::Personaje(QGraphicsItem *parent,int vida, int energia)
    :vida(10), energia(1),arma(nullptr) {} // Inicializamos sin arma al inicio

//Personaje::Personaje(QGraphicsItem *parent)
//    : vida(1), energia(1), arma(nullptr) {} // Inicializamos sin arma al inicio

void Personaje::equiparArma(const shared_ptr<Arma>& nuevaArma) {
    arma = nuevaArma;
}

void Personaje::recibirDano(int dano) {
    vida -= dano;
    if (vida <= 0) {
        scene()->removeItem(this);
        delete this;
    }
}

int Personaje::getVida(){ return vida; }

int Personaje::getEnergia(){ return energia; }

shared_ptr<Arma> Personaje::getArma(){return arma;}
