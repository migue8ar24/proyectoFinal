#include "Juego.h"
using namespace std;

Juego::Juego(const Personaje& personajePrincipal)
    : jugador(personajePrincipal) {}

void Juego::agregarEnemigo(const shared_ptr<Personaje>& enemigo) {
    enemigos.push_back(enemigo);
}

void Juego::iniciarJuego() {
    mostrarEstado(); // Agregar lógica
}

void Juego::actualizarJuego() {
    // Interacción entre el personaje , enemigos, obstaculos, etc
    mostrarEstado(); // Muestra el estado actual después de la interacción
}

void Juego::mostrarEstado() {
    //Lógica mostrar el Estado (vida habilidades) en cada frame
}
