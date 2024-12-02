#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <memory> // Para utilizar punteros inteligentes
#include <QGraphicsRectItem>
#include "Arma.h"
#include "BateDeBeisbol.h"

class Personaje: public QObject {
private:
    int vida;
    std::shared_ptr<Arma> arma; // Puntero inteligente para manejar el arma

public:
    // Constructor con valores predeterminados
    Personaje(int vida, QGraphicsItem* parent = nullptr);

    int getVida() const {return vida;};
    void setVida(int newVida) {vida = newVida;};
    void recibirDano(int dano);
    void equiparArma(const std::shared_ptr<Arma>& nuevaArma);
    virtual void onDeath() = 0;
    std::shared_ptr<Arma> getArma();
    virtual ~Personaje() = default; // Destructor virtual por si alguna clase derivada lo necesita
};

#endif // PERSONAJE_H
