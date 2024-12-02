#ifndef HOMERO2_H
#define HOMERO2_H

#include "Personaje.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>
#include <QObject>

class Homero2 : public Personaje, public QGraphicsRectItem {
    Q_OBJECT  // Necesario para el uso de señales y ranuras

private:
    int cargaEspecial;
    bool enElAire;
    bool tenedor;
    bool barreraActiva;
    qreal velocidadY;
    const qreal gravedad;
    QTimer *timerSalto;
    QTimer *timerTenedor;  // Temporizador para lanzar el tenedor
    bool puedeLanzarTenedor;  // Indica si se puede lanzar el tenedor
    int ventanaActual; // Variable para gestionar la ventana actual
    QGraphicsRectItem *barreraVertical;
    QGraphicsRectItem *barreraHorizontal;
    int spriteIndex;  // Índice del sprite actual
    QString direccionActual; // Dirección actual ("D" o "I")

public:
    Homero2();

    // Métodos de la clase Homero
    void usarHabilidadEspecial();
    void recargarHabilidad();
    void keyPressEvent(QKeyEvent *event) override;
    void actualizar();  // Método para actualizar la física del salto
    void habilitarLanzarTenedor();
    void activarBarrera() { barreraActiva = true; }
    void desactivarBarrera() { barreraActiva = false; }
    void actualizarVentana(int nuevaVentana);
    void eliminarBarreras();
    void actualizarSprite();
    void onDeath() override;
    void plusCargaHabilidad();

    bool isBarreraActiva() const { return barreraActiva; }
    bool setTenedorTrue(){return tenedor=true;};
    bool getTenedor(){return tenedor;};

    int getventanaActual(){return ventanaActual;};
    int getHabilidad() const {return cargaEspecial;};

};

#endif // HOMERO2_H
