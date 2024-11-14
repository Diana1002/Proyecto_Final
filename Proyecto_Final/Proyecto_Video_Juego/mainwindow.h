#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include "objeto.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QElapsedTimer>

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

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    Objeto *Jugador=nullptr;
    QTimer *timer;
    //QElapsedTimer lastUpdateTime;
    float deltaDeTiempo = 0.1;
};
#endif // MAINWINDOW_H
