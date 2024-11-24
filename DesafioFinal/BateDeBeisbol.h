#ifndef BATEDEBEISBOL_H
#define BATEDEBEISBOL_H

#include "Arma.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

class BateDeBeisbol : public Arma, public QGraphicsEllipseItem {
public:
    BateDeBeisbol(QGraphicsItem *parent=0);
    QList<QGraphicsItem*> collidingItems() const override;
    void ataqueCircular(QGraphicsScene* escena, int radio,int _xPos,int _yPos);
    void hit();

public slots:
    void borrarBate();
};

#endif // BATEDEBEISBOL_H
