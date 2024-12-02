#include "Homero2.h"
#include "Lvl2.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include "Tenedor.h"

Homero2::Homero2()
    : Personaje(100,nullptr), cargaEspecial(100), enElAire(false), tenedor(false), barreraActiva(false),
    velocidadY(0), gravedad(9.8), puedeLanzarTenedor(true), ventanaActual(1),
    barreraVertical(nullptr), barreraHorizontal(nullptr), spriteIndex(1),
    direccionActual("D") {  // Inicializa el sprite en el primer estado
    setRect(0, 0, 80, 130); // Tamaño del personaje

    setPen(Qt::NoPen);

    // Inicializar el temporizador para manejar la física del salto
    timerSalto = new QTimer(this);
    connect(timerSalto, &QTimer::timeout, this, &Homero2::actualizar);  // Conectar el temporizador

    // Inicializar el temporizador para lanzar tenedor
    timerTenedor = new QTimer(this);
    connect(timerTenedor, &QTimer::timeout, this, &Homero2::habilitarLanzarTenedor);  // Rehabilitar lanzamiento después de 2 segundos

    // Inicializar el temporizador para recargar la habilidad
    QTimer *timerRecarga = new QTimer(this);
    connect(timerRecarga, &QTimer::timeout, this, &Homero2::recargarHabilidad);  // Recargar habilidad cada segundo
    timerRecarga->start(2000);  // Ejecutar cada 2000 ms (2 segundos)
}

void Homero2::keyPressEvent(QKeyEvent *event) {
    // Obtener los límites de la escena
    qreal sceneWidth = scene()->width();
    qreal sceneHeight = scene()->height();
    qreal margin = 10;  // Margen para evitar interacciones inmediatas al teletransportarse

    // Gestión de sprites
    static int estadoDerecha = 1;
    static int estadoIzquierda = 1;
    static int estadoLanzar = 1;

    // Controlar el movimiento según la ventana actual
    if (ventanaActual == 1) {
        if (event->key() == Qt::Key_Left) {
            if (x() > margin) {
                setPos(x() - 10, y());
            }
            // Cambiar sprite de movimiento izquierda
            setBrush(QPixmap(QString(":/spritesM/sprites/I%1.png").arg(estadoIzquierda)));
            estadoIzquierda = (estadoIzquierda % 10) + 1;  // Ciclar entre I1 e I10
        } else if (event->key() == Qt::Key_Right) {
            if (x() + rect().width() < sceneWidth) {
                setPos(x() + 10, y());
            } else {
                actualizarVentana(2);
                setPos(margin, y());
            }
            // Cambiar sprite de movimiento derecha
            setBrush(QPixmap(QString(":/spritesM/sprites/D%1.png").arg(estadoDerecha)));
            estadoDerecha = (estadoDerecha % 10) + 1;  // Ciclar entre D1 y D10
        }
    } else if (ventanaActual == 2) {
        if (event->key() == Qt::Key_Left) {
            if (x() > 0) {
                setPos(x() - 10, y());
            } else {
                actualizarVentana(1);
                setPos(sceneWidth - rect().width() - margin, y());
            }
            // Cambiar sprite de movimiento izquierda
            setBrush(QPixmap(QString(":/spritesM/sprites/I%1.png").arg(estadoIzquierda)));
            estadoIzquierda = (estadoIzquierda % 10) + 1;
        } else if (event->key() == Qt::Key_Right) {
            if (x() + rect().width() < sceneWidth) {
                setPos(x() + 10, y());
            } else {
                actualizarVentana(3);
                setPos(margin, y());
            }
            // Cambiar sprite de movimiento derecha
            setBrush(QPixmap(QString(":/spritesM/sprites/D%1.png").arg(estadoDerecha)));
            estadoDerecha = (estadoDerecha % 10) + 1;
        }
    } else if (ventanaActual == 3) {
        if (event->key() == Qt::Key_Left) {
            if (x() > 0) {
                setPos(x() - 10, y());
            } else {
                actualizarVentana(2);
                setPos(sceneWidth - rect().width() - margin, y());
            }
            // Cambiar sprite de movimiento izquierda
            setBrush(QPixmap(QString(":/spritesM/sprites/I%1.png").arg(estadoIzquierda)));
            estadoIzquierda = (estadoIzquierda % 10) + 1;
        } else if (event->key() == Qt::Key_Right) {
            if (x() + rect().width() < sceneWidth - margin) {
                setPos(x() + 10, y());
            }
            // Cambiar sprite de movimiento derecha
            setBrush(QPixmap(QString(":/spritesM/sprites/D%1.png").arg(estadoDerecha)));
            estadoDerecha = (estadoDerecha % 10) + 1;
        }
    }

    // Salto (solo si Homero no está en el aire)
    if (event->key() == Qt::Key_Space && !enElAire) {
        enElAire = true;          // Marcar que Homero está en el aire
        velocidadY = -20;         // Velocidad inicial hacia arriba (negativa)
        timerSalto->start(16);    // Iniciar el temporizador para actualizar el salto cada 16 ms (aproximadamente 60 FPS)
    }

    // Lanzamiento del tenedor
    if (event->key() == Qt::Key_T) {
        if (getTenedor() && puedeLanzarTenedor) {
            Tenedor *tenedor = new Tenedor(x() + rect().width(), y() + rect().height() - 80, 5);
            tenedor->setPos(x() + rect().width(), y() + rect().height() - 80);  // Posición inicial cerca de Homero
            scene()->addItem(tenedor);

            // Movimiento MRU: Comienza a moverse con velocidad constante
            QTimer::singleShot(0, [tenedor]() {
                tenedor->lanzar(); // Método que controla el MRU y la caída
            });

            // Desactivar la posibilidad de lanzar otro tenedor por 2 segundos
            puedeLanzarTenedor = false;
            timerTenedor->start(2000);  // Esperar 2 segundos antes de permitir otro lanzamiento
        }
    }

    // Habilidad especial
    if (event->key() == Qt::Key_H && cargaEspecial == 100) {
        usarHabilidadEspecial();
    }

    // Actualizar las barreras si existen
    if (barreraVertical) {
        barreraVertical->setPos(x() + rect().width(), y());
    }
    if (barreraHorizontal) {
        barreraHorizontal->setPos(x(), y() - 20);
    }
}

void Homero2::habilitarLanzarTenedor() {
    puedeLanzarTenedor = true;  // Permitir lanzar el tenedor después de 2 segundos
}

void Homero2::actualizar() {
    if (enElAire) {
        qreal nuevaY = y() + velocidadY;
        velocidadY += gravedad * 0.1;

        if (nuevaY >= scene()->height() - rect().height()) {
            nuevaY = scene()->height() - rect().height();
            enElAire = false;
            velocidadY = 0;
            timerSalto->stop();
        }

        setPos(x(), nuevaY);
    }

    // Actualizar las posiciones de las barreras
    if (barreraVertical) {
        barreraVertical->setPos(x() + rect().width(), y());
    }
    if (barreraHorizontal) {
        barreraHorizontal->setPos(x(), y() - 20);
    }
}


void Homero2::usarHabilidadEspecial() {
    if (getVida() <= 80) {
        setVida(getVida() + 20);
    }
    else if(getVida() == 90){
        setVida(100);
    }

    cargaEspecial = 0;  // Ponemos a 0 la carga especial después de usarla

    // Crear y añadir las barreras si no existen
    if (!barreraVertical) {
        barreraVertical = new QGraphicsRectItem();
        barreraVertical->setRect(0, 0, 60, 100);
        barreraVertical->setBrush(QPixmap(QString(":/spritesM/sprites/Escudo1.png")));
        barreraVertical->setPen(Qt::NoPen);
        barreraVertical->setPos(x(), y()); // Posición inicial
        scene()->addItem(barreraVertical);
    }

    if (!barreraHorizontal) {
        barreraHorizontal = new QGraphicsRectItem();
        barreraHorizontal->setRect(0, 0, 100, 60);
        barreraHorizontal->setBrush(QPixmap(QString(":/spritesM/sprites/escudo2.png")));
        barreraHorizontal->setPen(Qt::NoPen);
        barreraHorizontal->setPos(x(), y()); // Posición inicial
        scene()->addItem(barreraHorizontal);
        activarBarrera();
    }

    QTimer::singleShot(3000, this, [this]() {
        if (barreraVertical) {
            scene()->removeItem(barreraVertical);
            delete barreraVertical;
            barreraVertical = nullptr;
        }
        if (barreraHorizontal) {
            scene()->removeItem(barreraHorizontal);
            delete barreraHorizontal;
            barreraHorizontal = nullptr;
        }
        desactivarBarrera();
    });
}

void Homero2::recargarHabilidad() {
    if (cargaEspecial < 100) {
        cargaEspecial += 10;  // Recargar la habilidad en 5
        if (cargaEspecial > 100) {
            cargaEspecial = 100;  // Limitar a 100 el valor máximo
        }
    }
}

void Homero2::actualizarVentana(int nuevaVentana) {
    ventanaActual = nuevaVentana;
}

void Homero2::eliminarBarreras() {
    if (barreraVertical) {
        scene()->removeItem(barreraVertical);
        delete barreraVertical;
        barreraVertical = nullptr; // Limpiar el puntero
    }

    if (barreraHorizontal) {
        scene()->removeItem(barreraHorizontal);
        delete barreraHorizontal;
        barreraHorizontal = nullptr; // Limpiar el puntero
    }

    desactivarBarrera(); // Desactivar la bandera de barreras activas
}

void Homero2::onDeath(){
    if (scene()) {
        scene()->removeItem(this);
    }
    delete this;
}

void Homero2::plusCargaHabilidad()
{
    if (getHabilidad() <= 70){ cargaEspecial += 30;}
    else {cargaEspecial = 100;}
}
