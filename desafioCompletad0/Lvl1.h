#ifndef LVL1_H
#define LVL1_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "Alcalde.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void terminarJuego();
    ~MainWindow();
    void win();

private:
    Ui::MainWindow *ui;
    QGraphicsView * view;
    QGraphicsScene * scene;

public slots:
    void vidaT(Alcalde* alcalde, MainWindow* mainWindow);
};
#endif // LVL1_H
