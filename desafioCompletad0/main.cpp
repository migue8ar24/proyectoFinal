#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>
#include <QPixmap>
#include "Lvl1.h"
#include "Lvl2.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Crear ventana principal como menú
    QWidget menu;
    menu.setWindowTitle("Menu Principal");
    menu.resize(800, 600); // Aumentar el tamaño del menú

    // Configurar fondo con una imagen
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap("fondomenu.png").scaled(menu.size(), Qt::KeepAspectRatioByExpanding)));
    menu.setPalette(palette);
    menu.setAutoFillBackground(true);

    // Layout principal
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(&menu);

    // Espaciador para empujar los botones hacia abajo
    layoutPrincipal->addStretch();

    // Layout para los botones
    QHBoxLayout *layoutBotones = new QHBoxLayout();
    layoutPrincipal->addLayout(layoutBotones);

    // Botón para elegir el nivel 1
    QPushButton *botonLvl1 = new QPushButton("Nivel 1");
    botonLvl1->setStyleSheet("font-size: 24px; padding: 10px;"); // Ajustar estilo del botón
    layoutBotones->addWidget(botonLvl1);

    // Botón para elegir el nivel 2
    QPushButton *botonLvl2 = new QPushButton("Nivel 2");
    botonLvl2->setStyleSheet("font-size: 24px; padding: 10px;"); // Ajustar estilo del botón
    layoutBotones->addWidget(botonLvl2);

    // Conexión del botón Nivel 1
    QObject::connect(botonLvl1, &QPushButton::clicked, [&]() {
        MainWindow *lvl1 = new MainWindow();
        lvl1->show(); // Mostrar la ventana del nivel 1
        menu.close(); // Cerrar el menú
    });

    // Conexión del botón Nivel 2
    QObject::connect(botonLvl2, &QPushButton::clicked, [&]() {
        Juego *lvl2 = new Juego();
        lvl2->iniciarJuego(); // Mostrar la ventana del nivel 2
        menu.close(); // Cerrar el menú
    });

    // Mostrar el menú principal
    menu.show();

    return a.exec();
}
