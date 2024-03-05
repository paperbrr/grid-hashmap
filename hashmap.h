#pragma once


typedef struct Cell{
    
    //filled or not :D, 1 is true, 0 is false
    int filled;

    //cell pos, measured from top left
    int cellX;
    int cellY;

}Cell;


typedef struct {

    //cell list
    Cell** cellArr;

    //metadata
    int winH;
    int winW;
    int cellCount;
    int cellSize;

}Grid;


typedef enum{

    //options for finding cells, given a certain cell
    CELL_UP,
    CELL_DOWN,
    CELL_LEFT,
    CELL_RIGHT

}LookupOption;


typedef enum{

    //to fill or not to fill; that is the question
    UNFILL, //0
    FILL,   //1

}FillState;


//function declarations
Grid* createGrid(int winW, int winH, int cellSize);
Cell* cellFindFromPos(Grid* grid, int x, int y);
Cell* cellFindNeighbour(Grid* grid, Cell* cell, LookupOption dir);
void cellChangeInArea(Grid* grid, int x, int y, int w, int h, FillState fillState);
Cell** getFilledCells(Grid* grid);
void freeGrid(Grid* grid);

