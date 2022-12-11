//
// Created by jamie on 11/16/22.
//

#ifndef TETRISCLONE_TILE_H
#define TETRISCLONE_TILE_H

#define TILE_NULL 0
#define TILE_GHOST 1
#define TILE_CYAN 2
#define TILE_YELLOW 3
#define TILE_PURPLE 4
#define TILE_GREEN 5
#define TILE_RED 6
#define TILE_BLUE 7
#define TILE_ORANGE 8


class Tile
{
    int row, col;
    int tileType;

public:

    Tile();
    Tile(int tileType, int row, int col);

    int getRow() const;
    int getCol() const;
    int getTileType() const;

    void setRow(int row);
    void setCol(int col);
    void setPos(int row, int col);
    void setTileType(int tileType);

    void move(int dRow, int dCol);
};


#endif //TETRISCLONE_TILE_H
