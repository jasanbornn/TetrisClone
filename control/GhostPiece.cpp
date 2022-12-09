//
// Created by jamie on 12/8/22.
//

#include "GhostPiece.h"

GhostPiece::GhostPiece()
{
    this->type = NULL_PIECE;

    for (int i = 0; i < TILES_PER_PIECE; i++)
    {
        tiles[i] = Tile(TILE_GHOST, -1,-1);
    }
}

void GhostPiece::update(std::array<Tile,TILES_PER_PIECE> newTiles)
{
    for (int i = 0; i < TILES_PER_PIECE; i++)
    {
        tiles[i] = newTiles[i];
    }
}

std::array<Tile, TILES_PER_PIECE> GhostPiece::getTiles()
{
    return this->tiles;
}
