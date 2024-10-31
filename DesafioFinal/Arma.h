#ifndef ARMA_H
#define ARMA_H
#include <string>
using namespace std;

class Arma {
private:
    string nombre;
    int dano;
    int alcance;

public:
    Arma(const string& nombre, int dano, int alcance); //constructor
    virtual ~Arma() = default;

    virtual int getDano();
    virtual int getAlcance();
    virtual string getNombre();
};


#endif // ARMA_H
