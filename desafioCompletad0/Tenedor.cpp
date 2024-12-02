#include "Tenedor.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QObject>
#include <QPixmap>  // Para usar QPixmap con setBrush
#include <chrono>
#include <cmath> // Para funciones matemáticas, como pow

Tenedor::Tenedor(qreal xInicioHomero, qreal yInicioHomero, qreal velocidadX)
    : Arma(30, 400), velocidadX(velocidadX), velocidadY(0), enCaida(false), tiempoTranscurrido(0),
    xInicio(xInicioHomero), yInicio(yInicioHomero) {  // Inicializamos con daño y alcance
    setRect(0, 0, 80,35);  // Tamaño del rectángulo que representa el tenedor

    // Asignar el sprite del tenedor
    setBrush(QPixmap(":/spritesM/sprites/Tenedor.png"));

    setPen(Qt::NoPen);

    // Crear el temporizador para controlar el lanzamiento
    timerMovimiento = new QTimer(this);  // Aquí 'this' es un puntero a un QObject (que Tenedor hereda)
    connect(timerMovimiento, &QTimer::timeout, this, &Tenedor::lanzar);  // Conectar la señal 'timeout'

    // Iniciar el temporizador para que lance periódicamente
    timerMovimiento->start(20);  // Ejemplo: cada 20 ms para una animación suave
}

Tenedor::Tenedor()
    : Arma(30, 400), velocidadX(5), velocidadY(0), enCaida(false), tiempoTranscurrido(0) {  // Inicializamos con daño y alcance
    setRect(0, 0, 80, 35);  // Tamaño del rectángulo que representa el tenedor

    // Asignar el sprite del tenedor
    setBrush(QPixmap(":/spritesM/sprites/Tenedor.png"));

    setPen(Qt::NoPen);

    // Crear el temporizador para controlar el lanzamiento
    timerMovimiento = new QTimer(this);  // Aquí 'this' es un puntero a un QObject (que Tenedor hereda)
    connect(timerMovimiento, &QTimer::timeout, this, &Tenedor::lanzar);  // Conectar la señal 'timeout'

    // Iniciar el temporizador para que lance periódicamente
    timerMovimiento->start(20);  // Ejemplo: cada 20 ms para una animación suave
}

void Tenedor::lanzar() {
    // Movimiento horizontal (MRU)
    if (!enCaida) {
        setPos(x() + velocidadX, y());  // Mover horizontalmente desde la posición de inicio

        // Si el tenedor ha recorrido el alcance máximo (400 unidades), inicia la caída
        if (x() >= xInicio + alcanceMaximo) {  // La distancia recorrida es la posición inicial + alcance máximo
            enCaida = true;
            velocidadY = 0;  // Aseguramos que la velocidad inicial vertical es 0
        }
    }

    // Si el tenedor ha alcanzado el alcance máximo, comienza a caer
    if (enCaida) {
        tiempoTranscurrido += 0.02;  // Aumentamos el tiempo (ajustable dependiendo de la frecuencia del timer)

        velocidadY += gravedad * tiempoTranscurrido;  // Velocidad vertical aumenta debido a la gravedad
        setPos(x(), y() + velocidadY);  // Mover hacia abajo con la velocidad calculada

        // Verificar si el tenedor ha tocado el suelo (suponiendo que el suelo está en Y = scene()->height() - rect().height())
        if (y() >= scene()->height() - rect().height()) {
            setPos(x(), scene()->height() - rect().height());  // Aseguramos que se quede en el suelo
            QTimer::singleShot(5000, this, &Tenedor::eliminarTenedor);  // Elimina el tenedor después de 5 segundos
        }
    }
}

void Tenedor::eliminarTenedor() {
    scene()->removeItem(this);  // Eliminar el tenedor de la escena
    delete this;  // Eliminar la memoria ocupada por el tenedor
}

QList<QGraphicsItem*> Tenedor::collidingItems() const {
    return QGraphicsItem::collidingItems();
}
