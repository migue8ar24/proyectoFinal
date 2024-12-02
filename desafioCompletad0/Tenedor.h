#ifndef TENEDOR_H
#define TENEDOR_H

#include <Arma.h>
#include <QGraphicsRectItem>
#include <QTimer>

class Tenedor : public Arma, public QGraphicsRectItem {
    Q_OBJECT

public:
    Tenedor(qreal xInicio, qreal yInicio, qreal velocidadX);  // Recibe la posición de inicio de Homero
    Tenedor();
    ~Tenedor() = default;

    QList<QGraphicsItem*> collidingItems() const override;
    void lanzar();  // Método para lanzar el tenedor y simular su movimiento
    void eliminarTenedor();

private:
    QTimer *timerMovimiento;   // Timer para manejar el movimiento del tenedor
    qreal velocidadX;          // Velocidad horizontal (constante)
    qreal velocidadY;          // Velocidad vertical (inicializada a 0)
    bool enCaida;              // Si el tenedor ya ha comenzado a caer
    const qreal gravedad = 9.8;      // Gravedad para el movimiento parabólico
    const qreal alcanceMaximo = 400; // Alcance máximo en la dirección X
    qreal tiempoTranscurrido;    // Tiempo que ha pasado para la simulación de la caída
    qreal xInicio;            // Posición inicial en X
    qreal yInicio;            // Posición inicial en Y
};

#endif // TENEDOR_H
