#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <memory> // Para utilizar punteros inteligentes
#include "Arma.h"

class Personaje {
private:
    int vida;
    int energia;
    shared_ptr<Arma> arma; // Puntero inteligente para manejar el arma

public:
    Personaje(int vida, int energia);
    int getVida();
    int getEnergia();
    void recibirDano(int dano);
    void equiparArma(const shared_ptr<Arma>& nuevaArma);
    virtual void atacar(Personaje& objetivo)=0;
    virtual ~Personaje() = default;
};


#endif // PERSONAJE_H
