#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene>
#include <QGraphicsView>
//#include "objeto.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QElapsedTimer>
#include "jugadorreal.h"
#include  "jugadornpc.h"

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
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event) override;
    void actualizarSimulacion();
    void choque(Objeto &objeto1, Objeto &objeto2);
    void simulacionChoque();
    void actualizarMovimiento();

private:
    float deltaDeTiempo = 0.01;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QTimer *timer;
    jugadorReal* jugadorReal1 = nullptr;   // Instancia del jugadorReal
    jugadorNPC* jugadorNPC1 = nullptr;     // Instancia del jugadorNPC
};
#endif // MAINWINDOW_H
