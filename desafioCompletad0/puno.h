#ifndef PUNO_H
#define PUNO_H

#include "Arma.h"
#include "Arma.h"
#include "QGraphicsItem"
#include <QGraphicsPixmapItem>

class Puno : public Arma, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Puno(QGraphicsItem *parent=0);
    QList<QGraphicsItem*> collidingItems() const override;

public slots:
    void borrarGolpe();

private:
    QTimer* timerGolpe;
};

#endif // PUNO_H
