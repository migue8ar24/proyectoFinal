#ifndef SECUAZ_H
#define SECUAZ_H

#include <QGraphicsRectItem>
#include "Personaje.h"
#include "Cuchillo.h"
#include <QObject>
#include <QTimer>

class Secuaz : public Personaje, public QGraphicsRectItem    {
    Q_OBJECT

private:
    bool moviendoIzquierda;
    qreal velocidadX;
    qreal velocidadY;
    bool enElAire;
    const qreal gravedad;
    qreal distanciaRecorrida;
    QTimer *timerMovimiento;
    QTimer *timerSalto;
    int numeroColor;

    void lanzarCuchillo();  // Método para lanzar cuchillos

public:
    Secuaz(int numeroColor);
    void onDeath() override;

private slots:
    void mover();
    void actualizarSalto();
};

#endif // SECUAZ_H
