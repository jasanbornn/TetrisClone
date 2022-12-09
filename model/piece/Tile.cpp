//
// Created by jamie on 11/16/22.
//

#include "Tile.h"

Tile::Tile()
{
    this->row = 0;
    this->col = 0;
    this->tileType = TILE_NULL;
}

Tile::Tile(int tileType, int row, int col)
{
    this->tileType = tileType;
    this->row = row;
    this->col = col;
}

int Tile::getRow() const
{
    return this->row;
}

int Tile::getCol() const
{
    return this->col;
}

int Tile::getTileType() const
{
    return this->tileType;
}

void Tile::setRow(int r)
{
    this->row = r;
}

void Tile::setCol(int c)
{
    this->col = c;
}

void Tile::setPos(int r, int c)
{
    this->row = r;
    this->col = c;
}

void Tile::move(int dRow, int dCol)
{
    this->row += dRow;
    this->col += dCol;
}

void Tile::setTileType(int t)
{
    this->tileType = t;
}
