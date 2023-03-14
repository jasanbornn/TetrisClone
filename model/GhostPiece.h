//
// Created by jamie on 12/8/22.
//

#ifndef TETRISCLONE_GHOSTPIECE_H
#define TETRISCLONE_GHOSTPIECE_H


#include <array>
#include <memory>
#include "Tile.h"
#include "piece/Piece.h"

class GhostPiece
{
    int type;
    std::array<Tile,TILES_PER_PIECE> tiles;

public:
    GhostPiece();
    void update(std::array<Tile, TILES_PER_PIECE> newTiles);
    std::array<Tile,TILES_PER_PIECE> getTiles();
};


#endif //TETRISCLONE_GHOSTPIECE_H
