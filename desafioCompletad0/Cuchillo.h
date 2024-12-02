#ifndef CUCHILLO_H
#define CUCHILLO_H

#include "Arma.h"
#include <QGraphicsRectItem>
#include <QTimer>

class Cuchillo : public Arma, public QGraphicsRectItem {
    Q_OBJECT

private:
    qreal velocidadX;    // Componente horizontal de la velocidad
    qreal velocidadY;    // Componente vertical de la velocidad
    const qreal gravedad; // Aceleración gravitatoria
    QTimer *timer;        // Temporizador para actualizar la posición

public:
    Cuchillo(qreal xInicial, qreal yInicial, qreal velocidadInicial, qreal angulo);
    QList<QGraphicsItem*> collidingItems() const override;

    // Métodos
    void iniciarMovimiento();  // Comenzar el movimiento parabólico

public slots:
    void actualizarPosicion(); // Slot para actualizar la posición
};

#endif // CUCHILLO_H
