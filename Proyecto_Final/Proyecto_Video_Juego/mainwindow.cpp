#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), scene(new QGraphicsScene(this)), view(new QGraphicsView(scene, this)), nivel1(new Nivel(QPointF(450, 350), 200, 100, 150, 70))
{
    ui->setupUi(this);
    this->move(0, 0);
    this->setFixedSize(900, 700);
    scene->setSceneRect(0, 0, 900, 700);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(900, 700);
    setCentralWidget(view);

    // Añadir el objeto Nivel a la escena
    scene->addItem(nivel1);

    QString ruta = ":/Imagenes/carro_Jugador";
    QString ruta1 = ":/Imagenes/carro_NPC";

    // Ajustar la vista
    jugadorReal1 = new jugadorReal(QPointF(450, 350), ruta, QPointF(0.2, 0.2), 10.0);
    scene->addItem(jugadorReal1);

    QList<QPointF> RutaNPC = {QPointF(450,100),QPointF(450,300), QPointF(200,300), QPointF(200,300)};
    jugadorNPC1 = new jugadorNPC(QPointF(200, 100), ruta1, QPointF(0.2, 0.2), 17.0, RutaNPC);
    scene->addItem(jugadorNPC1);

    RutaNPC = { QPointF(450,300), QPointF(100,300),QPointF(100,100),QPointF(300,100)};
    jugadorNPC *jugadorNPC2= new jugadorNPC(QPointF(300,300), ruta1, QPointF(0.2, 0.2), 17.0, RutaNPC);
    scene->addItem(jugadorNPC2);

    // paredes como barreras
    //paredSuperior = scene->addRect(0, -5, 700, 5, QPen(Qt::NoPen), QBrush(Qt::black));
    //paredInferior = scene->addRect(0, 700, 900, 5, QPen(Qt::NoPen), QBrush(Qt::black));
    //paredIzquierda = scene->addRect(-5, 0, 5, 700, QPen(Qt::NoPen), QBrush(Qt::black));
    //paredDerecha = scene->addRect(900, 0, 5, 700, QPen(Qt::NoPen), QBrush(Qt::black));
    //scene->setBackgroundBrush(QBrush(QColor(0, 0, 51)));


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarSimulacion);
    timer->start(1); // Actualizar cada 100 ms
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
    view->centerOn(jugadorReal1);
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
    Velocidad2Final -= masa1*Velocidad2;
    Velocidad2Final += masa2*Velocidad2;
    Velocidad2Final /= (masa1+masa2);
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
        }
        else{
            float magnitud = sqrt(velocidad.x()*velocidad.x()+velocidad.y()*velocidad.y());
            aceleracion += -aceleracion*exp(deltaDeTiempo*(-1/k))*magnitud*0.005;
            velocidad += aceleracion*deltaDeTiempo; //v = v0 + a * deltaTiempo
            cambioPosicion += velocidad*deltaDeTiempo; //x = x0 + v * deltaTiempo
            ObjetoMovible->mover(cambioPosicion);
        }
        QList<QGraphicsItem*> Objetos = scene->collidingItems(ObjetoMovible);
        if(Objetos.isEmpty()){

            //Se setean todos los valores}
            ObjetoMovible->setAceleracion(aceleracion);
            ObjetoMovible->setVelocidad(velocidad);
        }
        else{
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
        jugadorNPC *NPC = dynamic_cast<jugadorNPC*>(ObjetoEnEscena);
        if(NPC)
        {
            QList<QPointF> Ruta=NPC->RutaNivel;
            int PosicionRuta = NPC->PosicionRuta;
            QPointF VectorDistancia = Ruta[PosicionRuta]-NPC->getPosicion();
            float DistanciaAlPunto=sqrt(QPointF::dotProduct(VectorDistancia, VectorDistancia));
            if(DistanciaAlPunto<=1)
            {
                NPC->siguientePunto();
                PosicionRuta = NPC->PosicionRuta;
                VectorDistancia = Ruta[PosicionRuta]-NPC->getPosicion();
                DistanciaAlPunto=sqrt(QPointF::dotProduct(VectorDistancia, VectorDistancia));
            }
            QPointF VectorNormal = VectorDistancia/DistanciaAlPunto;
            NPC->aplicarFuerza(VectorNormal*0.02);
        }

    }
}
