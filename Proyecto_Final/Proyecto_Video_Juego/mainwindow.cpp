#include "mainwindow.h"
#include "./ui_mainwindow.h"


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
    QString ruta = ":/Imagenes/carro_Jugador";
    QString ruta1 = ":/Imagenes/carro_NPC";

    //QPointF pos(2.0,3.0);
    //Objeto objeto(pos, ruta,QPointF(0.5 , 0.5)  );
    //Jugador = new Objeto(pos, ruta, QPointF(0.5 , 0.5), 10.0F);
    //scene->addItem(Jugador->imagenItem);
    // Ajustar la vista

    jugadorReal1 = new jugadorReal(QPointF(2.0, 3.0), ruta, QPointF(0.5, 0.5), 10.0);
    scene->addItem(jugadorReal1);
    jugadorNPC1 = new jugadorNPC(QPointF(200, 0), ruta1, QPointF(0.5, 0.5), 15.0);
    scene->addItem(jugadorNPC1);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(1000,700);

    setCentralWidget(view);


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarSimulacion);
    timer->start(1); // Actualizar cada 100 ms
    //lastUpdateTime.start();

    jugadorReal1->imagenItem->setFlag(QGraphicsItem::ItemIsFocusable);
    //jugadorReal1->imagenItem->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QPointF fuerza;
    switch (event->key()) {
    case Qt::Key_W:
        qDebug() << "Tecla W presionada - Mover hacia arriba";
        fuerza = QPointF(0,-10);
        //Jugador->mover(QPointF(0,-10));
        break;
    case Qt::Key_S:
        qDebug() << "Tecla S presionada - Mover hacia abajo";
        fuerza = QPointF(0,10);
        //Jugador->mover(QPointF(0, 10));  // Mover hacia abajo
        break;
    case Qt::Key_A:
        qDebug() << "Tecla A presionada - Mover hacia la izquierda";
        fuerza = QPoint(-10, 0);
        //Jugador->mover(QPointF(-10, 0)); // Mover hacia la izquierda
        break;
    case Qt::Key_D:
        qDebug() << "Tecla D presionada - Mover hacia la derecha";
        fuerza = QPoint(10,0);
        //Jugador->mover(QPointF(10, 0));  // Mover hacia la derecha
        break;
    default:
        QMainWindow::keyPressEvent(event); // Llamada a la implementación por defecto
        return;
    }
    // Aplicar la fuerza al objeto
    jugadorReal1->aplicarFuerza(fuerza);

}
void MainWindow::actualizarSimulacion()
{
    //float tiempo = lastUpdateTime.restart() / 1000.0f; // Calcula delta en segundos

    // Llamar al método de actualizarMovimiento del objeto
    jugadorReal1->actualizarMovimiento(deltaDeTiempo);
    simulacionChoque();
    //Crear funcion para detectar colisiones (todos los objetos con masa)
    //Si se detecta que dos objetos se estan colicionando,
    //hacer una funcion a la cual se le pase el objeto 1 y 2 ( los objetos que estan chocando
    //y aplicarle la solucuion de las ecuaciones de choque (las que debo despejar)
    //Las colisiones se detectan antes de moverlo NO DESPUES
    // Verificar posición, velocidad, y aceleración
    //QPointF pos = jugadorReal1->getPosicion();
    //QPointF vel = jugadorReal1->getVelocidad();
    //QPointF acel = jugadorReal1->getAceleracion();

    //qDebug() << "Posición:" << pos << "Velocidad:" << vel << "Aceleración:" << acel;
}

void MainWindow::choque(QGraphicsItem* objeto1, QGraphicsItem* objeto2)
{
    if (objeto1->collidesWithItem(objeto2)) {
        qDebug() << "Colisión detectada entre los dos objetos.";
    } else {
        qDebug() << "No hay colisión.";
    }
}

void MainWindow::simulacionChoque()
{
    QList <QGraphicsItem*> objEnScene = scene->items();
    if (objEnScene.isEmpty()){
        qDebug() <<"No hay objetos en escena";
        return;
    }
    foreach (QGraphicsItem* item, objEnScene) {
        //qDebug() <<"La posicion de este objeto es"<<item->pos();
        QList <QGraphicsItem*> objetosChocando = scene->collidingItems(item);
        if (objetosChocando.isEmpty()){
            continue;
        }
        foreach (QGraphicsItem* objChocando, objetosChocando){

        }
    }
}
