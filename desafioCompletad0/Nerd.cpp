#include "Nerd.h"
#include "Alcalde.h"
#include "QTimer"
#include "QGraphicsScene"
#include <cmath>



Nerd::Nerd(QGraphicsItem *parent): Personaje(10,parent){
    srand(time(0));
    sprite = (rand() % 6);
    QPixmap pixmap;
    if (sprite == 0){
        pixmap.load(":/spritesM/sprites/SpNerd1.png");
    }
    else if (sprite == 1){
        pixmap.load(":/spritesM/sprites/SpNerd2.png");
    }
    else if (sprite == 2){
        pixmap.load(":/spritesM/sprites/SpNerd3.png");

    }
    else if (sprite == 3){
        pixmap.load(":/spritesM/sprites/SpNerd4.png");

    }
    else if (sprite == 4){
        pixmap.load(":/spritesM/sprites/SpNerd5.png");
    }

    QPixmap scaledPixmap = pixmap.scaled(80, 80);
    setPixmap(scaledPixmap);

    int random_number = rand() % 670;
    setPos(0,random_number);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

bool Nerd::move(){
    int change;
    this->t += 0.5;
    srand(time(0));
    int amplitud = (rand() % 30);
    change = amplitud*cos((M_PI/2)*this->t);
    setPos(x()+5,y()+change);  // y = A cos (w*t)
    if (pos().x() > 1500){
        scene()->removeItem(this);
        delete this;

    }
    else if ((pos().y() > 720) ||(pos().y() <0)){
        scene()->removeItem(this);
        delete this;
    }
}

void Nerd::onDeath(){
    if (scene()) {
        scene()->removeItem(this);
    }
    delete this;
}
