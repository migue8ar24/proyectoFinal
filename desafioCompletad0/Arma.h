#ifndef ARMA_H
#define ARMA_H
#include <QObject>
#include <QGraphicsItem>
#include <QMainWindow>

using namespace std;

class Arma : public QObject {
    Q_OBJECT

private:
    int dano;
    int alcance;

public:
    Arma(int dano, int alcance); //constructor

    QGraphicsItem* touch();
    virtual int getDano();
    virtual int getAlcance();

    virtual QList<QGraphicsItem*> collidingItems() const = 0;
    virtual ~Arma() = default;
};


#endif // ARMA_H
