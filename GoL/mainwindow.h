#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <vector>
#include <QMainWindow>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWindow *parent = nullptr);
    ~MainWindow() {}

    void render(QPainter *painter);

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void exposeEvent(QExposeEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent* ev);
    void checkCell(int row, int col);

private:
    QBackingStore backingStore; // drawing area
    bool        update_pending;
    std::vector<std::vector<bool>> cells;
    std::vector<std::vector<bool>> checkCells;
    int         bredde;
    int         hoyde;
    bool        pause;
};

#endif // MAINWINDOW_H
