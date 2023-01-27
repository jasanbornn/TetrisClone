//
// Created by jamie on 11/13/22.
//

#include <iostream>
#include <memory>
#include "Piece.h"


Piece::Piece(int row, int col)
{
    this->rotation = ROT_ZERO;
}

void Piece::move(int dRow, int dCol)
{
    for (Tile& tile: tiles)
    {
        tile.move(dRow, dCol);
    }
}

std::array<Tile, TILES_PER_PIECE>& Piece::getTiles()
{
    return this->tiles;
}

std::array<Tile, TILES_PER_PIECE> Piece::getRelativeTiles()
{
    std::array<Tile, TILES_PER_PIECE> relativeTiles = tiles;

    int relativeRow = tiles[0].getRow();
    int relativeCol = tiles[0].getCol();

    for (Tile& tile: relativeTiles)
    {
        tile.setRow(tile.getRow() - relativeRow);
        tile.setCol(tile.getCol() - relativeCol);
    }

    return relativeTiles;
}

int Piece::getRotation() const
{
    return this->rotation;
}

int Piece::getType() const
{
    return this->type;
}

void Piece::rotateLeft()
{

}

void Piece::rotateRight()
{

}

void Piece::setPos(int row, int col)
{
    rotation = ROT_ZERO;
}

void Piece::resetTiles()
{
    rotation = ROT_ZERO;
}

