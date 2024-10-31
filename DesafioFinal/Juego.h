#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include <memory>
#include "Personaje.h"

class Juego {
private:
    shared_ptr<Personaje> jugador; //se usa un puntero a que Personaje es una clase abstracta
    vector<std::shared_ptr<Personaje>> enemigos;

public:
    Juego(shared_ptr<Personaje> personajePrincipal);

    void iniciarJuego();
    void mostrarEstado(); // Mostrar vida, habilidad de Homero, etc
    void actualizarJuego(); // Aquí iría la lógica para cada frame o ciclo del juego
    void agregarEnemigo(const shared_ptr<Personaje>& enemigo); // enemigos.push_back(enemigo);
};

#endif // JUEGO_H

