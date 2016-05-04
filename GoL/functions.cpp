
void Functions::checkCell(int row, int col) {
    int numberAlive = 0;
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

    for(int i=fromRow;i<=toRow;i++){
        for(int j=fromCol;j<=toCol;j++) {
            if(i == row && j == col) {

            }
            else if(checkCells[i][j]) {
                numberAlive++;
            }
        }
    }

    //levende celler med mindre enn to naboer dør
    if(checkCells[row][col] && (numberAlive < 2)) {
        cells[row][col] = false;
    }

    //levende celler med to eller tre naboer lever videre
    else if(checkCells[row][col] && (numberAlive == 2 || numberAlive == 3)) {
        cells[row][col] = true;
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

void Functions::readFile(string filnavn, int forfx, int forfy) {
    ifstream file;
    file.open(filnavn);

    if(file.is_open()) {
        int x;
        int y;
        string line;


        while(getline(file, line)) {

            if(line[0] != '#') {
                istringstream iss(line);
                iss >> x >> y;
                cells[x+forfx][y+forfy] = true;

            }

        }
    }
}
