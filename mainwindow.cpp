#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    brushLine(QColor(255,0,0)), // konstruktor obiektu klasy QBrush
    penLine(brushLine, 4)
{
    ui->setupUi(this);

    image = new QImage(800, 300, QImage::Format_ARGB32); // tworzę bitmapę o rozmiarze 800 x 300 z 32 bitową głębią kolorów
    image->fill(QColor(255, 255, 255)); // wypełniam bitmapę kolorem białym

    paintOnImage = new QPainter; // tworzę obiekt klasy QPainter
    paintOnImage->begin(image); // podpinam grafikę pod obiekt klasy QPainter
    paintOnImage->setPen(penLine); // ustawiam pędzel rysowania

}

MainWindow::~MainWindow()
{
    delete ui;

    paintOnImage->end(); // kończę rysowanko po bitmapie
    delete image; // usuwam bitmapę
    delete paintOnImage; // usuwam obiekt klasy rysującej po bitmapie

}

void MainWindow::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);

    QPainter painter;
    painter.begin(this);

    painter.drawImage(0, 0, *image); // rysowanie utworzonej wcześniej bitmapy

    painter.end();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){

    QWidget::mouseMoveEvent(event);

    if(event->buttons() & Qt::LeftButton){ // jeżeli lewy przycisk mychy został wciśnięty to
        paintOnImage->drawLine(mousePos.x() , mousePos.y(), event->x(), event->y()); // rysuję linię od ostatnio odnotowanego punktu do bieżącego

        // zapamiętuję punkt
        mousePos.setX(event->x());
        mousePos.setY(event->y());

        repaint(); // odrysowuję okno
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    // trzeba zapamiętać punkt kliknięcia myszką
    mousePos.setX(event->x());
    mousePos.setY(event->y());
}
