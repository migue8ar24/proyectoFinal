#ifndef LVL2_H
#define LVL2_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <memory>
#include <QString>
#include "Homero2.h"
#include "Personaje.h"
#include "Tenedor.h"

class Juego: public QObject {
    Q_OBJECT

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    std::shared_ptr<Homero2> jugador;
    QGraphicsPixmapItem* vidaItem;
    QGraphicsPixmapItem* habilidadItem;
    Tenedor* tenedor;
    bool tenedorCreado = false;
    bool secuacesCreados = false;
    int ventanaCargada;

public:
    Juego();
    void agregarEnemigo(std::shared_ptr<Personaje> enemigo);
    void iniciarJuego();
    void mostrarEstado();
    void actualizarVentana();
    void verificarColisiones();
    void terminarJuego();
    void win();
};

#endif // LVL2_H
