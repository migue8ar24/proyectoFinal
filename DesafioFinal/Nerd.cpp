#include "Nerd.h"
#include "QTimer"
#include "QGraphicsScene"
#include <cmath>
void Nerd::atacar(Personaje& objetivo) {}

Nerd::Nerd(QGraphicsItem *parent): Personaje(parent){
    int random_number = rand() % 670;
    setPos(0,random_number);
    setRect(0,0,50,50);

    // connect
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

void Nerd::move(){
    int change;
    this->t += 0.5;
    srand(time(0));
    int amplitud = (rand() % 30);
    change = amplitud*cos((M_PI/2)*this->t);
    setPos(x()+5,y()+change);  // y = A cos (w*t)
    if (pos().x() + rect().width() > 1550){
        scene()->removeItem(this);
        delete this;
    }
}
