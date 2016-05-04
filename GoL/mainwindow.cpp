#include "mainwindow.h"
#include "readfile.cpp"
#include "readfile.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

MainWindow::MainWindow(QWindow *parent) : QWindow{parent}, backingStore{this}
{
    // Lager vinduet og setter høyde, bredde og geometri
    create();
    pause = false;
    bredde = 200;
    hoyde = 200;
    setGeometry(bredde, hoyde, bredde*3, hoyde*3); // set resolution of window

    readFile fileReader;
    //filnavn, forflytning(x), forflytning(y)
    cells = fileReader.read(cells, "1.lif", 100, 50, hoyde, bredde);
}

//Hovedfunskjonen for rendering
void MainWindow::renderNow()
{
    //Definerer området
    QRect rect(0, 0, width(), height());
    backingStore.beginPaint(rect);

    //Lager en tegneenhet
    QPaintDevice *device = backingStore.paintDevice();
    QPainter painter(device);

    //Lager hvit bakgrunn
    painter.fillRect(0, 0, width(), height(), Qt::white);
    render(&painter);

    backingStore.endPaint();
    backingStore.flush(rect);

    //hvis P er trykket, stopper animasjonen
    if(!pause) {
        checkCells = cells;

        auto t_start = chrono::high_resolution_clock::now();
        for(int i = 30;i<hoyde;i++) {
            for(int j=30;j<bredde;j++) {
                checkCell(i, j);
            }
        }
        auto t_end = chrono::high_resolution_clock::now();
        double time = chrono::duration<double, milli>(t_end-t_start).count();

        std::cout << time;
        pause = true;


    }

    renderLater();
}

//Funksjon for å tegne i vindu
void MainWindow::render(QPainter *painter)
{
    //Setter innstillinger til pennen
    QPen linepen(Qt::black);
    linepen.setWidth(3);
    painter->setPen(linepen);
    painter->setBrush(Qt::NoBrush);

    //Går gjennom hele vektoren og tegner representerte piksler
    for (int row = 0; row < hoyde; row++) {
        for (int col = 0; col < bredde; col++) {
            if(cells[row][col]) {
                painter->drawPoint(row*3,col*3);
            }
        }
    }


}

//Funksjon for tastatur-events
void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    readFile fileReader;
    //hvis Q er trykket, stopp applikasjonen
    if(ev->key() == Qt::Key_Q) {
        QGuiApplication::quit();
    }

    //hvis P er trykket, pause animasjonen
    if(ev->key() == Qt::Key_P && !pause) {
        pause = true;
    }

    //hvis P er trykket og animasjonen er pauset, fortsett animasjonen
    else if(ev->key() == Qt::Key_P && pause) {
        pause = false;
    }

    else if(ev->key() == Qt::Key_1) {
        cells = fileReader.remake(cells, "1.lif", 100, 50, hoyde, bredde);
    }

    else if(ev->key() == Qt::Key_2) {
        cells = fileReader.remake(cells, "2.lif", 100, 50, hoyde, bredde);
    }

    else if(ev->key() == Qt::Key_3) {
        cells = fileReader.remake(cells, "3.lif", 100, 50, hoyde, bredde);
    }
}

/**************
 * Følgende funksjoner er standard  Qt-funksjoner
 *************/

bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::UpdateRequest) {
        update_pending = false;
        renderNow();
        return true;
    }
    return QWindow::event(event);
}

void MainWindow::renderLater()
{
    if (!update_pending) {
        update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void MainWindow::resizeEvent(QResizeEvent *resizeEvent)
{
    backingStore.resize(resizeEvent->size());
    if (isExposed())
        renderNow();
}

void MainWindow::exposeEvent(QExposeEvent *)
{
    if (isExposed()) {
        renderNow();
    }
}

/***********
 * Følgende funksjoner er egendefinert
 * *********/

void MainWindow::checkCell(int row, int col) {
    int numberAlive = 0;

    //Ordner kantene så den ikke går utenfor
    int fromRow = row-1;
    int toRow = row+1;

    int fromCol = col-1;
    int toCol = col+1;

    if(row == 0) {
        fromRow++;
    }

    else if(row == hoyde-1) {
        toRow--;
    }

    if(col == 0) {
        fromCol++;
    }

    else if(col == bredde-1) {
        toCol--;
    }

    //Går gjennom alle naboene til en celle og sjekker hvor mange som er levende
    for(int i=fromRow;i<=toRow;i++){
        for(int j=fromCol;j<=toCol;j++) {
            if(checkCells[i][j] && !(i==row && j==col)) {
                numberAlive++;
            }
        }
    }

    //levende celler med mindre enn to naboer dør
    if(checkCells[row][col] && (numberAlive < 2)) {
        cells[row][col] = false;
    }

    //levende celler med mer enn tre levende naboer dør
    else if(checkCells[row][col] && numberAlive > 3) {
        cells[row][col] = false;
    }

    //døde celler med nøyaktig 3 naboer lever igjen
    else if(!checkCells[row][col] && numberAlive == 3) {
        cells[row][col] = true;
    }
}
