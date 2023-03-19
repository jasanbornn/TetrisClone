//
// Created by jamie on 11/13/22.
//

#ifndef TETRISCLONE_BOARD_H
#define TETRISCLONE_BOARD_H

#include <vector>
#include <array>
#include "Tile.h"
#include "piece/Piece.h"

#define BOARD_HEIGHT 40
#define BOARD_WIDTH 10


class Board
{
    int width;
    int height;

    std::array<std::array<Tile, BOARD_WIDTH>, BOARD_HEIGHT> tiles;

public:
    Board();

    void addTile(Tile tile);

    void removeTile(int row, int col);

    Tile getTile(int row, int col);

    std::array<std::array<Tile, BOARD_WIDTH>, BOARD_HEIGHT> getTiles() const;

    void addPiece(Piece piece);

    void clearLines();
};


#endif //TETRISCLONE_BOARD_H
