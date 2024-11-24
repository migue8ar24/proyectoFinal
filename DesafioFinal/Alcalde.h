#ifndef ALCALDE_H
#define ALCALDE_H

#include "Personaje.h"

class Alcalde : public Personaje {
public:
    Alcalde();
    void atacar(Personaje& objetivo) override;
};

#endif // ALCALDE_H
