#include "Juego.h"

Juego::Juego(shared_ptr<Personaje> personajePrincipal)
    : jugador(personajePrincipal) {}

void Juego::iniciarJuego() {}

void Juego::mostrarEstado() {}

void Juego::actualizarJuego() {// Aquí va la lógica para actualizar el juego en cada frame
}

void Juego::agregarEnemigo(const shared_ptr<Personaje>& enemigo) {
    enemigos.push_back(enemigo); // Agrega un enemigo a la lista
}

