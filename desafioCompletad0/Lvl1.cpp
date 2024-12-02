#include "ui_Lvl1.h"
#include "Lvl1.h"
#include "Homero.h"
#include "BateDeBeisbol.h"
#include "Alcalde.h"
#include "QGraphicsRectItem"
#include "QTimer"
#include "QGraphicsScene"
#include <QImage>
#include <QBrush>
#include <QGraphicsTextItem>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Añadir una escena, vista y limitar ambas
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    scene->setBackgroundBrush(QBrush(QImage(":/fondos/fondo.png")));

    view ->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view ->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view -> show();
    view -> setFixedSize(1080,720);
    scene -> setSceneRect(0,0,1080,720);//1550,780

    //crear homero
    Homero * homer = new Homero();
    homer->setPos(view->width()- 200,view->height()/2 );
    scene->addItem(homer);

    //manejo del personaje principal
    homer -> setFlag(QGraphicsItem::ItemIsFocusable);
    homer -> setFocus();

    //incluir alcalde
    Alcalde* alcalde = new Alcalde();
    alcalde->setPos(view->width()- 80,0);
    scene->addItem(alcalde);


    //spawn enemigos
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),homer,SLOT(spawnNerd()));
    timer->start(6000);


    //vida y carga
    QGraphicsTextItem* vidaText = new QGraphicsTextItem();
    QGraphicsTextItem* cargaText = new QGraphicsTextItem();

    vidaText->setDefaultTextColor(Qt::black);
    cargaText->setDefaultTextColor(Qt::black);

    vidaText->setFont(QFont("Japanese", 16));
    cargaText->setFont(QFont("Japanese", 16));

    vidaText->setPos(10, 50);   // Position at top-left
    cargaText->setPos(10, 80); // Position below vidaText

    scene->addItem(vidaText);
    scene->addItem(cargaText);

    // Update text items whenever Homero's attributes change
    QTimer* updateTimer = new QTimer(this);
    QObject::connect(updateTimer, &QTimer::timeout, this, [=]() {
        vidaText->setPlainText(QString("Vida: %1").arg(alcalde->getVida()));
        if (homer->getArma()!=nullptr){
            cargaText->setPlainText(QString("Carga Especial: %1").arg(homer->getCarga()));
        }
    });
    updateTimer->start(100); // Refresh every 100ms

    //dificultad
    QTimer::singleShot(60000, this, [timer](){
        timer->setInterval(2000);
    });

    // arma especial
    //semilla para generacion aleatoria de ubicacion
    srand(time(0));

    //generacion de powerup

    int col = (rand() % 1080);
    int fila = (rand() % 720);
    BateDeBeisbol* bate = new BateDeBeisbol();
    bate->setPos((col+20),(fila+20));
    scene->addItem(bate);

    //recarga powerup
    QTimer * timerCarga = new QTimer();
    QObject::connect(timerCarga,SIGNAL(timeout()),homer,SLOT(recargarHabilidad()));
    timerCarga->start(1000);

    QTimer * timerC = new QTimer();
    QObject::connect(timerC,SIGNAL(timeout()),alcalde,SLOT(colision()));
    QObject::connect(timerC, &QTimer::timeout, this, [=]() { vidaT(alcalde, this); });
    //QObject::connect(timerC,SIGNAL(timeout()),this,SLOT(vidaT(alcalde,this)));

    timerC->start(100);

    //finalizar nivel
    QTimer::singleShot(100000, this, [this](){
        win();
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::vidaT(Alcalde* alcalde, MainWindow* mainWindow) {
    if (alcalde->getVida() <= 0) {
        mainWindow->terminarJuego(); // Use the provided pointer
    }
}


void MainWindow::terminarJuego() {

    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : scene->items()) {
        if (scene == item->scene() ) { // Verificar si pertenece a la escena actual
            scene->removeItem(item);
            delete item; // Liberar memoria
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

void MainWindow::win(){

    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : scene->items()) {
        if (scene == item->scene()) {
            scene->removeItem(item);
            delete item;
        }
    }


    scene->setBackgroundBrush(QBrush(Qt::black));


    QGraphicsTextItem* winGame = new QGraphicsTextItem("YOU WIN!");
    winGame->setDefaultTextColor(Qt::red);
    winGame->setFont(QFont("Arial", 32, QFont::Bold));
    winGame->setPos(scene->width() / 2 - 100, scene->height() / 2 - 50);
    scene->addItem(winGame);

    QTimer::singleShot(4000, this, [this]() {
        view->close();
        QApplication::quit();
    });

}
