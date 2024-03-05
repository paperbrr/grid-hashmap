#include "hashmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int hashPos(Grid* grid, int x, int y) {

    /*
    basically translates the two dimensions into a single dimension and scales, so that the point 'given' turns
    into the indice in a 1-d array if the whole thing was just a 1-d array.
    [1,2,3
     4,5,6     -> in here, 6 is at [1,2]. this is translated into 5, indice of 6 in [1,2,3,4,5,6,7,8,9]
     7,8,9]
    */

    //hash, maintain uniquenes
    int hashedPos = (y/grid->cellSize)*(grid->winW/grid->cellSize)+(x/grid->cellSize);
    return hashedPos;

}


Grid* createGrid(int winW, int winH, int cellSize){

    //allocate memory for grid, cellsArr
    int cellCount = (winW*winH)/(cellSize*cellSize);
    Grid* grid = malloc(sizeof(Grid));
    grid->cellArr = malloc(sizeof(Cell*)*cellCount*2);  //reduces the chances of collision! (actually no but will work on this)
    if (grid->cellArr==NULL || grid==NULL){printf("error allocating memory for grid");return NULL;}

    //grid init
    grid->cellCount = cellCount;
    grid->winH = winH;
    grid->winW = winW;
    grid->cellSize = cellSize;

    //iterate through ALL spaces,
    for (int y=0; y<winH; y+=cellSize){
        for (int x=0; x<winW; x+=cellSize){
    
            //create and init cell
            Cell* newCell = malloc(sizeof(Cell));
            if (newCell==NULL) {printf("error allocating memory for cell"); return NULL;}
            newCell->cellX = x; newCell->cellY = y;
            newCell->filled = 0;

            //assign cell to grid after hashing key
            grid->cellArr[hashPos(grid, x, y)] = newCell;
        }
    }
    return grid;

}


Cell* cellFindFromPos(Grid* grid, int x, int y){

    //snap pos, hash key
    x = 30*floor((double) x/grid->cellSize);
    y = 30*floor((double) y/grid->cellSize);
    int arrIndex = hashPos(grid, x, y);


    //assign hashed key if valid
    if (arrIndex>=0 && arrIndex<grid->cellCount){
        return grid->cellArr[arrIndex];
    }

    printf("no cell located");
    return NULL;

}


Cell* cellFindNeighbour(Grid* grid, Cell* cell, LookupOption dir){
    
    int cellSize = grid->cellSize;

    //switch through look up options; return appropriate positions and associated cells
    switch (dir){
        case CELL_UP:
            return cellFindFromPos(grid, cell->cellX, cell->cellY-cellSize);
        case CELL_DOWN:
            return cellFindFromPos(grid, cell->cellX, cell->cellY+cellSize);
        case CELL_LEFT:
            return cellFindFromPos(grid, cell->cellX-cellSize, cell->cellY);
        case CELL_RIGHT:
            return cellFindFromPos(grid, cell->cellX+cellSize, cell->cellY);
    }

    return NULL;

}


void cellChangeInArea(Grid* grid, int x, int y, int w, int h, FillState fillState){

    //changes fill state of the cell in the given area
    for (int i=x; i<x+w; i+=grid->cellSize){
        for (int j=y; j<y+h; j+=grid->cellSize){
            Cell* cell = cellFindFromPos(grid, i, j);
            if (cell){
                if (cell->filled == fillState){
                    printf("attempted to overwrite fill state of cell with same fill state");
                }
                else {
                    cell->filled = fillState;
                }
            }
        }
    }

}


Cell** getFilledCells(Grid* grid){

    //returns an array of all filled cells
    Cell** filledCells = malloc(sizeof(Cell*) * grid->cellCount);
    int filledCount = 0;
    for (int i=0;i<grid->cellCount;i++){
       if (grid->cellArr[i]->filled==FILL){
        filledCells[i] = grid->cellArr[i];
        filledCount += 1;
       }
    }
    filledCells = realloc(filledCells, sizeof(Cell*)*filledCount);

    return filledCells;
} 


void freeGrid(Grid* grid){

    //frees the grid
    for (int i=0; i<grid->cellCount; i++){
        free(grid->cellArr[i]);
    }    

    //freeing metadata
    grid->cellCount = 0;
    grid->cellSize = 0;
    grid->winH = 0;
    grid->winW = 0;

}