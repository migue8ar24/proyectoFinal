#ifndef PERSONAJE_H
#define PERSONAJE_H


#include <QGraphicsRectItem>
#include <memory> // Para utilizar punteros inteligentes

#include "Arma.h"
#include "BateDeBeisbol.h"

class Personaje: public QObject, public QGraphicsRectItem{

private:
    int vida;
    int energia;
    shared_ptr<Arma> arma; // Puntero inteligente para manejar el arma

public:
    //Personaje(QGraphicsItem *parent = nullptr);
    Personaje(QGraphicsItem *parent = nullptr,int vida= 10, int energia= 10);
    int getVida();
    int getEnergia();
    void setVida();
    void recibirDano(int dano);
    void equiparArma(const shared_ptr<Arma>& nuevaArma);
    virtual void atacar(Personaje& objetivo)=0;
    virtual ~Personaje() = default;
    shared_ptr<Arma> getArma();

};


#endif // PERSONAJE_H
