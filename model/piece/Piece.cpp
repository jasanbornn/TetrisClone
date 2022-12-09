//
// Created by jamie on 11/13/22.
//

#include <iostream>
#include <memory>
#include "Piece.h"


Piece::Piece(int xPos, int yPos)
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

void Piece::moveUp()
{
    this->move(-1,0);
}

void Piece::moveDown()
{
    this->move(1, 0);
}

void Piece::moveLeft()
{
    this->move(0, -1);
}

void Piece::moveRight()
{
    this->move(0, 1);
}

std::array<Tile, TILES_PER_PIECE>& Piece::getTiles()
{
    return this->tiles;
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
