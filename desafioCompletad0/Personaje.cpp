#include "Personaje.h"
#include "QGraphicsScene"
#include "QGraphicsItem"
#include "BateDeBeisbol.h"

Personaje::Personaje(int vida, QGraphicsItem* parent)
    :vida(vida),arma(nullptr) {} // Inicializamos sin arma al inicio

void Personaje::recibirDano(int dano) {
    vida -= dano;
    if (vida <= 0) {
        vida = 0;
    }
}

void onDeath();

void Personaje::equiparArma(const std::shared_ptr<Arma>& nuevaArma) {
    arma = nuevaArma;
}

std::shared_ptr<Arma> Personaje::getArma(){return arma;}

