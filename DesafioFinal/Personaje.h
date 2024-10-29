#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <string>
#include <memory> // Para utilizar punteros inteligentes
#include "Arma.h"

class Personaje {
private:
    int vida;
    int energia;
    string nombre;
    shared_ptr<Arma> arma; // Puntero inteligente para manejar el arma

public:
    Personaje(const string& nombre, int vida, int energia);
    int getVida();
    int getEnergia();
    string getNombre();
    void recibirDano(int dano);
    void equiparArma(const shared_ptr<Arma>& nuevaArma);
};


#endif // PERSONAJE_H
