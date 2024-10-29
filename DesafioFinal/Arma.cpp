#include <Arma.h>
#include <string>
using namespace std;

Arma::Arma(const string &nombre, int dano, int alcance)
    :nombre(nombre), dano(dano), alcance(alcance){}

//getters

int Arma::getDano() {return dano;}
int Arma::getAlcance(){return alcance;}
string Arma::getNombre(){return nombre;}
