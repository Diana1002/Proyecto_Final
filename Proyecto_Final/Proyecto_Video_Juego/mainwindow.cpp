#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "objeto.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), scene(new QGraphicsScene(this)), view(new QGraphicsView(scene, this))
{
    ui->setupUi(this);

    /*
    // Cargar imagen de la pista
    QPixmap background("C:\\Users\\Asus\\Documents\\DIANA BAEZA RUIZ\\SEMESTRE 2024-2\\Lab Info 2\\Proyecto_Prueba\\Imagenes\\pista1.png");
    if (background.isNull()){
        qDebug() << "No se pudo cargar la imagen";
        return;
    }
    // Agregar imagen de fondo de la pista a la escena
    QGraphicsPixmapItem *backgroundItem = new QGraphicsPixmapItem(background);
    scene->addItem(backgroundItem);
    scene->setSceneRect(0, 0, background.width(), background.height());
    */
    QString ruta = "C:\\Users\\Asus\\Documents\\DIANA BAEZA RUIZ\\SEMESTRE 2024-2\\Lab Info 2\\Proyecto_Prueba\\Imagenes\\carro.png";
    QPointF pos(2.0,3.0);
    Objeto objeto(pos, ruta, QPointF(0.5 , 0.5) );
    scene->addItem(objeto.imagenItem);
    // Ajustar la vista
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(1000,700);

    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        qDebug() << "Tecla W presionada - Mover hacia arriba";
        moverCarro(0, -10); // Mover hacia arriba
        break;
    case Qt::Key_S:
        qDebug() << "Tecla S presionada - Mover hacia abajo";
        moverCarro(0, 10);  // Mover hacia abajo
        break;
    case Qt::Key_A:
        qDebug() << "Tecla A presionada - Mover hacia la izquierda";
        moverCarro(-10, 0); // Mover hacia la izquierda
        break;
    case Qt::Key_D:
        qDebug() << "Tecla D presionada - Mover hacia la derecha";
        moverCarro(10, 0);  // Mover hacia la derecha
        break;
    default:
        QMainWindow::keyPressEvent(event); // Llamada a la implementación por defecto
    }
}
