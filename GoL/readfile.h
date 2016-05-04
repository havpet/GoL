#ifndef READFILE_H
#define READFILE_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


class readFile
{
public:
    readFile();
    ~readFile();
    std::vector<std::vector<bool>> read(std::vector<std::vector<bool>> cells, string filnavn, int forfx, int forfy, int hoyde, int bredde);
    std::vector<std::vector<bool>> remake(std::vector<std::vector<bool>> cells, string filnavn, int forfx, int forfy, int hoyde, int bredde);

private:
    int             x;
    int             y;
    ifstream        file;
    string          line;


};

#endif // READFILE_H
