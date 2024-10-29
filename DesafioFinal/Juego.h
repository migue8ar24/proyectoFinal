#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include "Personaje.h"

class Juego {
private:
    Personaje jugador;
    vector<shared_ptr<Personaje>> enemigos;

public:
    Juego(const Personaje& personajePrincipal);
    void iniciarJuego();
    void mostrarEstado(); // Mostrar vida, habilidad de homero, etc
    void actualizarJuego();// Aquí iría la lógica para cada frame o ciclo del juego, como el movimiento de enemigos, ataques, y colisiones
    void agregarEnemigo(const shared_ptr<Personaje>& enemigo); //enemigos.push_back(enemigo);
};


#endif // JUEGO_H
