#ifndef FUNCTIONS
#define FUNCTIONS

#include <QtGui>
#include <vector>
#include <QMainWindow>

class Functions
{
protected:
    void checkCell(int row, int col);
    void readFile(string filnavn, int forfx, int forfy);

private:
    QBackingStore backingStore; // drawing area
    bool        update_pending;
    std::vector<std::vector<bool>> cells;
    std::vector<std::vector<bool>> checkCells;
    int         bredde;
    int         hoyde;
    QMutex      sync;
    QWaitCondition pauseCond;
    bool pause;
};

#endif // FUNCTIONS

