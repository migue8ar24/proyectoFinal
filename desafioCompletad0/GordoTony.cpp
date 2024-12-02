#include "GordoTony.h"
#include "Tenedor.h"
#include <QGraphicsScene>
#include <QTimer>

GordoTony::GordoTony()
    : Personaje(510, nullptr),
    moviendoIzquierda(true),
    velocidadX(2),
    velocidadY(0),
    enElAire(false),
    gravedad(9.8),
    distanciaRecorrida(0),
    movimientoRapido(false),
    ciclosPorFrame(6),       // Cambiar sprite cada 6 ciclos
    contadorFrames(0)        // Inicia en 0
{
    setRect(0, 0, 140, 140); // Tamaño de GordoTony

    setBrush(QPixmap(":/spritesM/sprites/GT15.png"));

    setPen(Qt::NoPen);

    // Temporizador para mover y saltar a GordoTony
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &GordoTony::mover);
    timerMovimiento->start(16); // Actualización cada 16 ms (60 FPS)

    // Temporizador para controlar el salto
    timerSalto = new QTimer(this);
    connect(timerSalto, &QTimer::timeout, this, &GordoTony::actualizarSalto);
}


void GordoTony::mover() {
    static int estadoQuieto = 1;
    static int contadorQuieto = 0;

    if (getVida() > 270) {
        // Antes de moverse, mostrar sprites de quieto durante 2 segundos
        if (contadorFrames < 120) { // 2 segundos a 60 FPS
            if (contadorQuieto % 60 == 0) { // Cambiar sprite cada segundo
                setBrush(QPixmap(QString(":/spritesM/sprites/GTI%1.png").arg(estadoQuieto)));
                estadoQuieto = (estadoQuieto % 2) + 1; // Ciclar entre GTI1 y GTI2
            }
            contadorQuieto++;
            contadorFrames++;
            return; // No hacer movimiento todavía
        }
        movimientoOriginal();
    } else {
        // Alternar entre movimiento rápido y original
        if (movimientoRapido) {
            movimientoExtremo();
        } else {
            movimientoOriginal();
        }

        // Alternar comportamiento cada cierto tiempo
        static int contador = 0;
        contador++;
        if (contador >= 200) { // Cambiar después de 200 ciclos
            movimientoRapido = !movimientoRapido;
            contador = 0;
        }
    }

    contadorFrames++;
}

void GordoTony::movimientoOriginal() {
    static int estadoIzquierda = 1;
    static int estadoDerecha = 1;
    static const int ciclosPorFrameOriginal = 10; // Hacerlo más lento

    if (!enElAire) {
        if (moviendoIzquierda) {
            setPos(x() - velocidadX, y());
            distanciaRecorrida += velocidadX;

            // Cambiar sprite de movimiento hacia la izquierda
            if (static_cast<int>(distanciaRecorrida) % ciclosPorFrameOriginal == 0) {
                setBrush(QPixmap(QString(":/spritesM/sprites/GTOI%1.png").arg(estadoIzquierda)));
                estadoIzquierda = (estadoIzquierda % 4) + 1; // Ciclar entre GTOI1 a GTOI8
            }

            if (distanciaRecorrida >= 350) {
                distanciaRecorrida = 0;
                enElAire = true;
                velocidadY = -30;
                timerSalto->start(16); // Comienza el salto
            }
        } else {
            setPos(x() + velocidadX, y());
            distanciaRecorrida += velocidadX;

            // Cambiar sprite de movimiento hacia la derecha
            if (static_cast<int>(distanciaRecorrida) % ciclosPorFrameOriginal == 0) {
                setBrush(QPixmap(QString(":/spritesM/sprites/GTOD%1.png").arg(estadoDerecha)));
                estadoDerecha = (estadoDerecha % 4) + 1; // Ciclar entre GTOD1 a GTOD8
            }

            if (distanciaRecorrida >= 350) {
                distanciaRecorrida = 0;
                enElAire = true;
                velocidadY = -30;
                timerSalto->start(16); // Comienza el salto
            }
        }
    }
}

void GordoTony::movimientoExtremo() {
    static int estadoExtremo = 1;
    static const int ciclosPorFrameExtremo = 15; // Más lento que movimiento original

    if (moviendoIzquierda) {
        setPos(x() - 10, y()); // Movimiento rápido hacia la izquierda
        if (contadorFrames % ciclosPorFrameExtremo == 0) {
            setBrush(QPixmap(QString(":/spritesM/sprites/GTE%1.png").arg(estadoExtremo)));
            estadoExtremo = (estadoExtremo % 10) + 1; // Ciclar entre GTE1 a GTE10
        }

        if (x() <= 0) {
            moviendoIzquierda = false;
        }
    } else {
        setPos(x() + 10, y()); // Movimiento rápido hacia la derecha
        if (contadorFrames % ciclosPorFrameExtremo == 0) {
            setBrush(QPixmap(QString(":/spritesM/sprites/GTE%1.png").arg(estadoExtremo)));
            estadoExtremo = (estadoExtremo % 10) + 1; // Ciclar entre GTE1 a GTE10
        }

        if (x() + rect().width() >= scene()->width()) {
            moviendoIzquierda = true;
        }
    }
}

void GordoTony::actualizarSalto() {
    static int estadoSalto = 1;
    static const int ciclosPorFrameSalto = 20; // Más lento para salto

    if (enElAire) {
        qreal nuevaY = y() + velocidadY;
        velocidadY += gravedad * 0.1; // Gravedad

        if (contadorFrames % ciclosPorFrameSalto == 0) {
            setBrush(QPixmap(QString(":/spritesM/sprites/GTS%1.png").arg(estadoSalto)));
            estadoSalto = (estadoSalto % 5) + 1; // Ciclar entre GTS1 a GTS5
        }

        if (nuevaY >= scene()->height() - rect().height()) {
            nuevaY = scene()->height() - rect().height();
            enElAire = false;
            velocidadY = 0;
            timerSalto->stop(); // Detener el temporizador del salto

            // Lanzar el tenedor
            Tenedor *tenedor = new Tenedor(x(), y(), -10);
            scene()->addItem(tenedor);
            tenedor->setBrush(QPixmap(":/spritesM/sprites/Viento.png"));
            tenedor->setPos(x() - 90, y() + 110);

            // Cambiar de dirección de movimiento
            moviendoIzquierda = !moviendoIzquierda;
        }

        setPos(x(), nuevaY);
    }
}

void GordoTony::onDeath(){
    if (scene()) {
        scene()->removeItem(this);
    }
    delete this;
}
