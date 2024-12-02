#include "Secuaz.h"
#include <QTimer>
#include <QGraphicsScene>
#include "Cuchillo.h"

Secuaz::Secuaz(int numeroColor)
    : Personaje(300,nullptr), moviendoIzquierda(true), velocidadX(2), velocidadY(0), enElAire(false), gravedad(9.8), distanciaRecorrida(0), numeroColor(numeroColor) {

    setRect(0, 0, 100, 140); // Tamaño del secuaz

    // Temporizador para mover y saltar al secuaz
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Secuaz::mover);
    timerMovimiento->start(16); // Actualización cada 16 ms (60 FPS)

    // Temporizador para controlar el salto
    timerSalto = new QTimer(this);
    connect(timerSalto, &QTimer::timeout, this, &Secuaz::actualizarSalto);
}

void Secuaz::mover() {
    static int estadoIzquierda = 1;
    static int estadoDerecha = 1;
    static int contadorFrames = 0; // Contador para controlar la velocidad del cambio de sprites
    const int ciclosPorFrame = 6;  // Cambiar sprite cada 5 ciclos de `mover`

    if (!enElAire) {
        QString spritePrefix;

        // Determinar el prefijo del sprite según el atributo numeroColor
        if (numeroColor == 0) {
            spritePrefix = "SA"; // Secuaz Amarillo
        } else if (numeroColor == 1) {
            spritePrefix = "SV"; // Secuaz Verde
        }

        if (moviendoIzquierda) {
            setPos(x() - velocidadX, y());
            distanciaRecorrida += velocidadX;

            // Cambiar sprite de movimiento hacia la izquierda cada ciertos ciclos
            if (contadorFrames % ciclosPorFrame == 0) {
                setBrush(QPixmap(QString(":/spritesM/sprites/%1I%2.png").arg(spritePrefix).arg(estadoIzquierda)));
                estadoIzquierda = (estadoIzquierda % 3) + 1; // Ciclar entre I1, I2, I3
            }

            // Lanzar cuchillo cuando recorre suficiente distancia
            if (distanciaRecorrida >= 150) {
                lanzarCuchillo();
                distanciaRecorrida = 0; // Reiniciar la distancia
                enElAire = true;        // Iniciar el salto
                velocidadY = -20;       // Velocidad inicial hacia arriba
                timerSalto->start(16);  // Iniciar el temporizador del salto
            }
        } else {
            setPos(x() + velocidadX, y());
            distanciaRecorrida += velocidadX;

            // Cambiar sprite de movimiento hacia la derecha cada ciertos ciclos
            if (contadorFrames % ciclosPorFrame == 0) {
                setBrush(QPixmap(QString(":/spritesM/sprites/%1D%2.png").arg(spritePrefix).arg(estadoDerecha)));
                estadoDerecha = (estadoDerecha % 3) + 1; // Ciclar entre D1, D2, D3
            }

            // Lanzar cuchillo cuando recorre suficiente distancia
            if (distanciaRecorrida >= 150) {
                lanzarCuchillo();
                distanciaRecorrida = 0; // Reiniciar la distancia
                enElAire = true;        // Iniciar el salto
                velocidadY = -20;       // Velocidad inicial hacia arriba
                timerSalto->start(16);  // Iniciar el temporizador del salto
            }
        }
    }

    // Incrementar el contador de frames
    contadorFrames++;
}

void Secuaz::actualizarSalto() {
    if (enElAire) {
        qreal nuevaY = y() + velocidadY;
        velocidadY += gravedad * 0.1; // Aceleración por gravedad

        // Verificar si el secuaz ha tocado el suelo
        if (nuevaY >= scene()->height() - rect().height()) {
            nuevaY = scene()->height() - rect().height();
            enElAire = false;        // El secuaz ya no está en el aire
            velocidadY = 0;          // Detener la velocidad vertical
            timerSalto->stop();      // Detener el temporizador del salto

            // Cambiar de dirección
            moviendoIzquierda = !moviendoIzquierda;
        }

        setPos(x(), nuevaY);
    }
}

void Secuaz::lanzarCuchillo() {
    // Crear el cuchillo en la posición actual del secuaz
    qreal velocidadInicial = 10;  // Velocidad inicial para el cuchillo
    qreal angulo = 110;  // Ángulo de lanzamiento (hacia la izquierda)

    // Lanzar el cuchillo
    Cuchillo *cuchillo = new Cuchillo(x(), y(), velocidadInicial, angulo);
    scene()->addItem(cuchillo);
    cuchillo->iniciarMovimiento(); // Iniciar el movimiento del cuchillo
}

void Secuaz::onDeath(){
    if (scene()) {
        scene()->removeItem(this);
    }
    delete this;
}
