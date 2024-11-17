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

    jugadorReal1->setFlag(QGraphicsItem::ItemIsFocusable);
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
    int Magnitud=1000;
    switch (event->key()) {
    case Qt::Key_W:
        qDebug() << "Tecla W presionada - Mover hacia arriba";
        fuerza = QPointF(0,-Magnitud);
        //Jugador->mover(QPointF(0,-10));
        break;
    case Qt::Key_S:
        qDebug() << "Tecla S presionada - Mover hacia abajo";
        fuerza = QPointF(0,Magnitud);
        //Jugador->mover(QPointF(0, 10));  // Mover hacia abajo
        break;
    case Qt::Key_A:
        qDebug() << "Tecla A presionada - Mover hacia la izquierda";
        fuerza = QPoint(-Magnitud, 0);
        //Jugador->mover(QPointF(-10, 0)); // Mover hacia la izquierda
        break;
    case Qt::Key_D:
        qDebug() << "Tecla D presionada - Mover hacia la derecha";
        fuerza = QPoint(Magnitud,0);
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
    actualizarMovimiento();
    //jugadorReal1->actualizarMovimiento(deltaDeTiempo);
    //simulacionChoque();
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


void MainWindow::choque(Objeto &objeto1, Objeto &objeto2)
{
    //Se extraen los datos
    float masa1=objeto1.masa;
    float masa2=objeto2.masa;
    QPointF Velocidad1=objeto1.getVelocidad();
    QPointF Velocidad2=objeto2.getVelocidad();
    QPointF Velocidad2Final = 2*masa1*Velocidad1;
    //Se aplican las ecuaciones de choque elastico

    Velocidad2Final-= masa1*Velocidad2;
    Velocidad2Final+=masa2*Velocidad2;
    Velocidad2Final/= (masa1+masa2);
    QPointF Velocidad1Final = Velocidad2Final +Velocidad2 - Velocidad1;
    objeto1.setVelocidad(Velocidad1Final);
    objeto2.setVelocidad(Velocidad2Final);
    return;
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
            if(item==objChocando){
                continue;
            }
            Objeto *objeto1= qgraphicsitem_cast<Objeto*>(item);
            Objeto *objeto2 = qgraphicsitem_cast<Objeto*>(objChocando);
            if(!objeto1 or !objeto2){
                return;
            }
            choque(*objeto1, *objeto2);
        }
    }
}

void MainWindow::actualizarMovimiento()
{

    QList<QGraphicsItem*> ObjetosEnEscena = scene->items();
    foreach(QGraphicsItem* ObjetoEnEscena, ObjetosEnEscena){
        Objeto *ObjetoMovible = qgraphicsitem_cast<Objeto*>(ObjetoEnEscena);
        if(!ObjetoMovible)
            continue;

        QPointF aceleracionInicial=ObjetoMovible->getAceleracion();
        QPointF velocidadInicial = ObjetoMovible->getVelocidad();

        float k = 0.5;
        QPointF aceleracion=aceleracionInicial;
        QPointF velocidad = velocidadInicial;
        QPointF cambioPosicion = QPointF(0,0);
        if (abs(aceleracion.x())<=0.001 && abs(aceleracion.y())<=0.001){
            aceleracion = QPointF(0,0);
            velocidad *= 0.95;
            cambioPosicion +=velocidad*deltaDeTiempo;

            ObjetoMovible->setAceleracion(aceleracion);
            ObjetoMovible->setVelocidad(velocidad);
            ObjetoMovible->mover(cambioPosicion);
            continue;
        }
        float magnitud = sqrt(velocidad.x()*velocidad.x()+velocidad.y()*velocidad.y());
        aceleracion += -aceleracion*exp(deltaDeTiempo*(-1/k))*magnitud*0.001;
        velocidad += aceleracion*deltaDeTiempo; //v = v0 + a * deltaTiempo
        cambioPosicion += velocidad*deltaDeTiempo; //x = x0 + v * deltaTiempo

        ObjetoMovible->mover(cambioPosicion);
        QList<QGraphicsItem*> Objetos = scene->collidingItems(ObjetoMovible);
        if(Objetos.isEmpty()){

            //Se setean todos los valores}
            ObjetoMovible->setAceleracion(aceleracion);
            ObjetoMovible->setVelocidad(velocidad);
            continue;
        }
        ObjetoMovible->mover(-cambioPosicion);
        foreach(QGraphicsItem *objeto , Objetos){
            Objeto *objetodechoque = qgraphicsitem_cast<Objeto*>(objeto);
            if(!objetodechoque)
            {
                qDebug() << "El objeto con que choca el objeto movible es un nullptr";
            }
            choque(*ObjetoMovible, *objetodechoque);
        }
    }

}
