#ifndef SECUAZ_H
#define SECUAZ_H

#include "Personaje.h"

class Secuaz : public Personaje {
public:
    Secuaz();
    void atacar(Personaje& objetivo) override;
};

#endif // SECUAZ_H
