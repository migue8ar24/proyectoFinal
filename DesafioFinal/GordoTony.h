#ifndef GORDOTONY_H
#define GORDOTONY_H

#include "Personaje.h"

class GordoTony : public Personaje {
public:
    GordoTony();
    void atacar(Personaje& objetivo) override;
};

#endif // GORDOTONY_H
