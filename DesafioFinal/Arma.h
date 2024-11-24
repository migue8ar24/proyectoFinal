#ifndef ARMA_H
#define ARMA_H
#include <string>
#include <QObject>
#include <QGraphicsItem>
#include <QMainWindow>


using namespace std;

class Arma:public QObject  {
    Q_OBJECT
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

    virtual QList<QGraphicsItem*> collidingItems() const = 0;
    QGraphicsItem* touch();
};


#endif // ARMA_H
