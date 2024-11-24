#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "Homero.h"
#include "BateDeBeisbol.h"
#include "QGraphicsRectItem"
#include "QTimer"
#include "QGraphicsScene"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();

    //Añadir una vista y limitarla
    view = new QGraphicsView(scene);
    view ->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view ->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //mostrar la vista y limitarla
    view -> show();
    view -> setFixedSize(1080,720);
    scene -> setSceneRect(0,0,1080,720);//1550,780

    Homero * homer = new Homero();
    homer->setPos(view->width()- homer->rect().width(),view->height()/2 );
    scene->addItem(homer);

    //manejo del personaje principal
    homer -> setFlag(QGraphicsItem::ItemIsFocusable);
    homer -> setFocus();

    //invocar los enemigos
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),homer,SLOT(spawnNerd()));
    timer->start(6000);

    // arma especial
    //semilla para generacion aleatoria de ubicacion
    srand(time(0));

    //generacion de obstaculos breakwalls

    int col = (rand() % 1080);
    int fila = (rand() % 720);
    BateDeBeisbol* bate = new BateDeBeisbol();
    bate->QGraphicsEllipseItem::setPos((col+20),(fila+20));
    scene->addItem(bate);


}

MainWindow::~MainWindow()
{
    delete ui;
}
