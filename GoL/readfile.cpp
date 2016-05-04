#include "readfile.h"

#include <fstream>
#include <sstream>
#include <string>

readFile::readFile()
{

}

readFile::~readFile()
{

}

std::vector<std::vector<bool>> readFile::read(std::vector<std::vector<bool>> cells, string filnavn, int forfx, int forfy, int hoyde, int bredde) {

    //fyller vector med døde celler
    for (int row = 0; row < hoyde; row++) {
        std::vector<bool> rows;
        cells.push_back(rows);
        for (int col = 0; col < bredde; col++) {
            cells[row].push_back(false);
        }
     }

    //åpner fil
    file.open(filnavn);

    //hvis fil er åpen
    if(file.is_open()) {

        //Går gjennom hver linje og skriver til x,y og deretter til vektoren
        while(getline(file, line)) {

            if(line[0] != '#') {
                istringstream iss(line);
                iss >> x >> y;
                cells[x+forfx][y+forfy] = true;
            }
        }
    }

    return cells;
}

std::vector<std::vector<bool>> readFile::remake(std::vector<std::vector<bool>> cells, string filnavn, int forfx, int forfy, int hoyde, int bredde) {

    //fyller vector med døde celler
    for (int row = 0; row < hoyde; row++) {
        for (int col = 0; col < bredde; col++) {
            cells[row][col] = false;
        }
     }

    //åpner fil
    file.open(filnavn);

    //hvis fil er åpen
    if(file.is_open()) {

        //Går gjennom hver linje og skriver til x,y og deretter til vektoren
        while(getline(file, line)) {

            if(line[0] != '#') {
                istringstream iss(line);
                iss >> x >> y;
                cells[x+forfx][y+forfy] = true;
            }
        }
    }

    return cells;
}

