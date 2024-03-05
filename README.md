# Grid-HashMap

Grid-HashMap is a C library for managing a **sparse** grid-based spatial hashmap, suited for applications where fast lookup is crucial (game development, computational geometry). It provides functionalities to create a grid, find cells based on coordinates, manage cell fill states, and retrieve filled cells.

## Features

- **Spatial Partitioning**
- **Grid Creation**: Easily create a grid with customizable dimensions and cell sizes.
- **Efficient Lookup**: Utilizes a hashmap to efficiently map 2D coordinates to cells.
- **Cell Management**: Functions to find cells, change fill states, and retrieve filled cells.
- **Memory Management**: Proper memory allocation and deallocation to prevent memory leaks.

## Installation

To use Grid-HashMap in your project, include the `hashmap.h` header file in your source files and link against the library during compilation.

## Usage

1. **Creating a Grid**: Use the `createGrid` function to initialize a grid with specified width, height, and cell size. (pixel units)

```c
Grid* grid = createGrid(winW, winH, cellSize);
```

2. **Finding Cells**: Locate a cell based on its coordinates using `cellFindFromPos`. The location is 'snapped' to a multiple of the cell size to locate the parent.

```c
Cell* cell = cellFindFromPos(grid, x, y);
```

3. **Managing Fill States**: Change the fill state of cells within a specified area using `cellChangeInArea`.

```c
cellChangeInArea(grid, x, y, w, h, fillState);
```

4. **Retrieving Filled Cells**: Get an array of filled cells using `getFilledCells`.

```c
Cell** filledCells = getFilledCells(grid);
```

5. **Freeing Memory**: Free the allocated memory when done using `freeGrid`.

```c
freeGrid(grid);
```

For more detailed information on each function and its parameters, refer to the comments within the source code.

## Contributing

Contributions to Grid-HashMap are welcome! If you find any issues or have suggestions, open an issue or submit a pull request.
