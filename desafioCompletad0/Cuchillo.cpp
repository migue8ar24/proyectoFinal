#include "Cuchillo.h"
#include <QtMath>
#include <QGraphicsScene>

Cuchillo::Cuchillo(qreal xInicial, qreal yInicial, qreal velocidadInicial, qreal angulo)
    : Arma(10, 0),  // Inicializar la clase base Arma con dano = 15 y alcance = 0
    velocidadX(velocidadInicial * qCos(qDegreesToRadians(angulo))),
    velocidadY(velocidadInicial * qSin(qDegreesToRadians(angulo))),
    gravedad(9.8) {

    // Tamaño del cuchillo
    setRect(0, 0, 80, 30);

    setBrush(QPixmap(":/spritesM/sprites/knife.png"));

    setPen(Qt::NoPen);

    // Posición inicial
    setPos(xInicial, yInicial);

    // Inicializar temporizador
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Cuchillo::actualizarPosicion);
}


void Cuchillo::iniciarMovimiento() {
    timer->start(16); // Actualizar cada ~16ms (60 FPS)
}

void Cuchillo::actualizarPosicion() {
    // Calcular la nueva posición
    qreal nuevaX = x() + velocidadX;
    qreal nuevaY = y() - velocidadY;

    // Actualizar la velocidad vertical (gravedad afecta solo el eje Y)
    velocidadY -= gravedad * 0.016;

    // Mover el cuchillo a la nueva posición
    setPos(nuevaX, nuevaY);

    // Verificar si el cuchillo ha salido de la escena
    if (scene() && (x() > scene()->width() || y() > scene()->height())) {
        scene()->removeItem(this); // Remover el cuchillo de la escena
        delete this;               // Liberar memoria
    }
}

QList<QGraphicsItem*> Cuchillo::collidingItems() const {
    return QGraphicsItem::collidingItems();
}
