#include "Personaje.h"
using namespace std;

Personaje::Personaje(const string& nombre, int vida, int energia)
    : nombre(nombre), vida(vida), energia(energia), arma(nullptr) {} // Inicializamos sin arma al inicio

void Personaje::equiparArma(const shared_ptr<Arma>& nuevaArma) {
    arma = nuevaArma;
}

void Personaje::recibirDano(int dano) {
    vida -= dano;
    if (vida <= 0) {
        // añadir lógica para "muerte" del personaje
    }
}

int Personaje::getVida(){ return vida; }
int Personaje::getEnergia(){ return energia; }
string Personaje::getNombre(){ return nombre; }
