#ifndef GORDOTONY_H
#define GORDOTONY_H

#include "Personaje.h"
#include <QGraphicsRectItem>
#include <QTimer>

class GordoTony : public Personaje, public QGraphicsRectItem {
    Q_OBJECT
public:
    GordoTony();
    void mover(); // Movimiento de GordoTony
    void actualizarSalto(); // Actualización del salto
    void movimientoOriginal();
    void movimientoExtremo();
    void onDeath() override;

private:

    int ciclosPorFrame; // Número de ciclos para cambiar de sprite
    int contadorFrames;
    bool moviendoIzquierda; // Dirección del movimiento
    bool movimientoRapido;
    bool enElAire; // Verificar si está saltando
    qreal velocidadX; // Velocidad en el eje X
    qreal velocidadY; // Velocidad en el eje Y
    qreal gravedad; // Gravedad aplicada al salto
    qreal distanciaRecorrida; // Distancia recorrida
    QTimer* timerMovimiento; // Temporizador para mover
    QTimer* timerSalto; // Temporizador para salto
};
#endif // GORDOTONY_H
