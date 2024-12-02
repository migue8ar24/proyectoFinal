#include "Lvl2.h"
#include "Homero2.h"
#include "Tenedor.h"
#include "Secuaz.h"
#include "GordoTony.h"
#include "qapplication.h"
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QBrush>
#include <QImage>
#include <QTimer>
#include <QGraphicsTextItem>

Juego::Juego() : ventanaCargada(0), tenedor(nullptr), vidaItem(nullptr), habilidadItem(nullptr) {
    // Crear la escena de Qt
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    // Crear el jugador (Homero)
    jugador = std::make_shared<Homero2>();
    jugador->setFlag(QGraphicsItem::ItemIsFocusable); // Permitir que Homero reciba eventos de teclado
    jugador->setFocus();
    scene->addItem(jugador.get());

    // Configurar el temporizador para verificar colisiones y transiciones de ventanas
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Juego::actualizarVentana);
    connect(timer, &QTimer::timeout, this, &Juego::verificarColisiones);
    timer->start(100); // Verificar cada 100 ms

    // Mostrar el estado del jugador en la pantalla
}

void Juego::iniciarJuego() {
    // Configurar la vista
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    view->setFixedSize(800, 600);
    scene->setSceneRect(0, 0, 800, 600);

    // Posicionar a Homero en la parte inferior central
    jugador->setPos(view->width() / 2, view->height() - jugador->rect().height());

    // Crear los elementos iniciales de la ventana
    actualizarVentana();
}

void Juego::mostrarEstado() {
    // Si ya existe el sprite de vida, lo eliminamos
    if (vidaItem) {
        scene->removeItem(vidaItem);
        delete vidaItem;
    }

    if (habilidadItem) {
        scene->removeItem(habilidadItem);
        delete habilidadItem;
    }

    // Calculamos el índice del sprite según la vida de Homero (invertido)
    int vida = jugador->getVida();
    int spriteIndex = (100 - vida) / 10;  // Esto asigna 0 -> V10, 10 -> V9, ..., 100 -> V1

    // Cargar el sprite correspondiente según la vida
    QGraphicsPixmapItem* spriteVida = new QGraphicsPixmapItem();
    QString spritePath = ":/spritesM/sprites/V" + QString::number(spriteIndex + 1) + ".png";  // Asegúrate que los archivos de sprite estén en el formato correcto
    spriteVida->setPixmap(QPixmap(spritePath));

    // Establecer la posición del sprite de vida
    spriteVida->setPos(10, 10);
    scene->addItem(spriteVida);  // Agregar el sprite a la escena

    // Guardamos el sprite para eliminarlo la próxima vez
    vidaItem = spriteVida;

    // Mostrar habilidad especial de Homero

    int Habilidad = jugador -> getHabilidad();
    int spriteIndex2 = (100 - Habilidad) / 10;

    QGraphicsPixmapItem* spriteHabilidad = new QGraphicsPixmapItem();
    QString spritePath2 = ":/spritesM/sprites/E" + QString::number(spriteIndex2 + 1) + ".png";  // Asegúrate que los archivos de sprite estén en el formato correcto
    spriteHabilidad->setPixmap(QPixmap(spritePath2));

    spriteHabilidad->setPos(30, 20);
    scene->addItem(spriteHabilidad);

    habilidadItem = spriteHabilidad;

}

void Juego::actualizarVentana() {
    int ventanaActual = jugador->getventanaActual(); // Obtener la ventana actual de Homero

    // Si la ventana ya está cargada, no hacer nada
    if (ventanaCargada == ventanaActual) {
        mostrarEstado();
        return;
    }

    // Cambiar el fondo y los elementos según la nueva ventana
    ventanaCargada = ventanaActual; // Actualizar la ventana cargada

    // Eliminar los elementos existentes de la escena (excepto al jugador, su vida y habilidad)
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        if (item != jugador.get() && item != vidaItem && item != habilidadItem) {
            scene->removeItem(item);
            delete item; // Liberar memoria
        }
    }

    // Configurar el contenido según la ventana actual
    switch (ventanaActual) {
    case 1:
        // Fondo de la ventana 1
        scene->setBackgroundBrush(QBrush(QImage("background1.jpg")));
        mostrarEstado();

        // Agregar un tenedor
        if (!tenedorCreado){

            tenedor = new Tenedor();
            tenedor->setPos(scene->width() - 150, scene->height() - 100); // Posicionar el tenedor
            scene->addItem(tenedor);

        }

        break;

    case 2:
        // Fondo de la ventana 2
        scene->setBackgroundBrush(QBrush(QImage("background2.jpg")));
        mostrarEstado();

        // Crear y posicionar los Secuaces solo si aún no han sido creados
        if (!secuacesCreados) {
            for (int i = 0; i < 2; ++i) {
                Secuaz* secuaz = new Secuaz(i);
                secuaz->setPos(scene->width() - 250 + i * 110, scene->height() - 140); // Alinear horizontalmente
                secuaz -> setPen(Qt::NoPen);
                scene->addItem(secuaz);
            }
            secuacesCreados = true; // Marcar que los secuaces ya han sido creados
        }

        break;

    case 3:
        // Fondo de la ventana 3
        scene->setBackgroundBrush(QBrush(QImage("background3.jpg")));
        mostrarEstado();

        // Crear el objeto GordoTony y posicionarlo en la parte derecha y pegado al suelo
        {
            GordoTony* gordoTony = new GordoTony();
            gordoTony->setPos(scene->width() - 100, scene->height() - 140); // Posicionar en la esquina derecha inferior
            scene->addItem(gordoTony);
        }

        break;

    default:
        break;
    }
}

void Juego::verificarColisiones() {
    // Verificar colisiones de Homero con tenedores
    if (tenedor && jugador->collidesWithItem(tenedor)) {
        scene->removeItem(tenedor); // Eliminar el tenedor de la escena
        jugador->setTenedorTrue();  // Equipar el tenedor a Homero
        delete tenedor;             // Liberar memoria
        tenedor = nullptr;

        tenedorCreado = true;
    }

    if (tenedorCreado) {
        QList<QGraphicsItem*> itemsTenedores = scene->items();
        for (QGraphicsItem* item : itemsTenedores) {
            auto* tenedor = dynamic_cast<Tenedor*>(item);
            if (tenedor && jugador->collidesWithItem(tenedor)) {
                if (!jugador->isBarreraActiva()) {
                    jugador->setVida(jugador->getVida() - tenedor->getDano());

                    if (jugador->getVida() <= 0) {
                        terminarJuego();
                        return;
                    }
                }

                scene->removeItem(tenedor);
                delete tenedor;
            }
        }
    }

    // Verificar colisiones de Homero con cuchillos
    QList<QGraphicsItem*> itemsCuchillos = scene->items();
    for (QGraphicsItem* item : itemsCuchillos) {
        auto* cuchillo = dynamic_cast<Cuchillo*>(item);
        if (cuchillo && jugador->collidesWithItem(cuchillo)) {
            if (!jugador->isBarreraActiva()) {
                jugador->setVida(jugador->getVida() - cuchillo->getDano());

                if (jugador->getVida() <= 0) {
                    terminarJuego();
                    return;
                }
            }

            scene->removeItem(cuchillo);
            delete cuchillo;
        }
    }

    // Verificar colisiones entre Homero y GordoTony
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        auto* gordoTony = dynamic_cast<GordoTony*>(item);
        if (gordoTony && jugador->collidesWithItem(gordoTony)) {
            if (!jugador->isBarreraActiva()) {
                jugador->setVida(jugador->getVida() - 20); // Daño que recibe Homero al colisionar con GordoTony

                if (jugador->getVida() <= 0) {
                    terminarJuego();
                    return;
                }
            }

            // GordoTony también puede recibir daño si tiene lógica de colisión específica
            gordoTony->setVida(gordoTony->getVida() - 10); // Daño al GordoTony

            if (gordoTony->getVida() <= 0) {
                scene->removeItem(gordoTony);
                delete gordoTony;
                win(); // Ganas si derrotas al GordoTony
                return;
            }
        }
    }

    // Verificar colisiones de Homero con secuaces
    for (QGraphicsItem* item : items) {
        auto* secuaz = dynamic_cast<Secuaz*>(item);
        if (secuaz && jugador->collidesWithItem(secuaz)) {
            jugador->setVida(jugador->getVida() - 10); // Daño de colisión con secuaz
            if (jugador->getVida() <= 0) {
                terminarJuego();
                return;
            }
        }
    }

    // Colisiones entre tenedores y enemigos
    QList<QGraphicsItem*> itemsSecuaces = scene->items();
    for (QGraphicsItem* item : itemsSecuaces) {
        auto* secuaz = dynamic_cast<Secuaz*>(item);
        if (secuaz) {
            for (QGraphicsItem* otherItem : itemsSecuaces) {
                auto* tenedor = dynamic_cast<Tenedor*>(otherItem);
                if (tenedor && secuaz->collidesWithItem(tenedor)) {
                    secuaz->setVida(secuaz->getVida() - tenedor->getDano());
                    scene->removeItem(tenedor);
                    delete tenedor;

                    if (secuaz->getVida() <= 0) {
                        scene->removeItem(secuaz);
                        delete secuaz;
                        break;
                    }
                }
            }
        }

        auto* gordoTony = dynamic_cast<GordoTony*>(item);
        if (gordoTony) {
            for (QGraphicsItem* otherItem : itemsSecuaces) {
                auto* tenedor = dynamic_cast<Tenedor*>(otherItem);
                if (tenedor && gordoTony->collidesWithItem(tenedor)) {
                    gordoTony->setVida(gordoTony->getVida() - tenedor->getDano());
                    jugador -> plusCargaHabilidad();
                    scene->removeItem(tenedor);
                    delete tenedor;

                    if (gordoTony->getVida() <= 0) {
                        scene->removeItem(gordoTony);
                        delete gordoTony;
                        win();
                        break;
                    }
                }
            }
        }
    }
}

void Juego::terminarJuego() {
    // Eliminar todos los elementos de la escena

    jugador -> eliminarBarreras();

    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : scene->items()) {
        if (item != jugador.get() && item != vidaItem && item != habilidadItem) {
            if (scene == item->scene()) { // Verificar si pertenece a la escena actual
                scene->removeItem(item);
                delete item; // Liberar memoria
            }
        }
    }

    // Establecer un fondo negro
    scene->setBackgroundBrush(QBrush(Qt::black));

    // Mostrar mensaje de "Game Over"
    QGraphicsTextItem* gameOverText = new QGraphicsTextItem("GAME OVER");
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setFont(QFont("Arial", 32, QFont::Bold));
    gameOverText->setPos(scene->width() / 2 - 100, scene->height() / 2 - 50);
    scene->addItem(gameOverText);

    // Salir del juego después de 4 segundos
    QTimer::singleShot(4000, this, [this]() {
        view->close(); // Cerrar la ventana del juego
        QApplication::quit(); // Finalizar la aplicación
    });
}

void Juego::win(){

    // Eliminar todos los elementos de la escena

    jugador -> eliminarBarreras();

    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : scene->items()) {
        if (item != jugador.get() && item != vidaItem && item != habilidadItem) {
            if (scene == item->scene()) { // Verificar si pertenece a la escena actual
                scene->removeItem(item);
                delete item; // Liberar memoria
            }
        }
    }

    // Establecer un fondo negro
    scene->setBackgroundBrush(QBrush(Qt::black));

    // Mostrar mensaje de "Game Over"
    QGraphicsTextItem* gameOverText = new QGraphicsTextItem("YOU WIN!");
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setFont(QFont("Arial", 32, QFont::Bold));
    gameOverText->setPos(scene->width() / 2 - 100, scene->height() / 2 - 50);
    scene->addItem(gameOverText);

    // Salir del juego después de 4 segundos
    QTimer::singleShot(4000, this, [this]() {
        view->close(); // Cerrar la ventana del juego
        QApplication::quit(); // Finalizar la aplicación
    });

}
