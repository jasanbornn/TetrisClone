//
// Created by jamie on 11/13/22.
//

#include "Board.h"

Board::Board()
{
    this->width = BOARD_WIDTH;
    this->height = BOARD_HEIGHT;

    for (int row = 0; row < BOARD_HEIGHT; row++)
    {
        for (int col = 0; col < BOARD_WIDTH; col++)
        {
            addTile(Tile(TILE_NULL, row, col));
        }
    }
}

void Board::addTile(Tile tile)
{
    this->tiles[tile.getRow()][tile.getCol()] = tile;
}

void Board::removeTile(int row, int col)
{
    this->tiles[row][col] = Tile(TILE_NULL, row, col);
}

Tile Board::getTile(int row, int col)
{
    return this->tiles[row][col];
}

std::array<std::array<Tile, BOARD_WIDTH>, BOARD_HEIGHT> Board::getTiles() const
{
    return this->tiles;
}

void Board::addPiece(Piece piece)
{
    for (auto& tile: piece.getTiles())
    {
        addTile(tile);
    }
}

int Board::clearLines()
{
    int numLines = 0;

    //Clear lines
    for (int row = 0; row < BOARD_HEIGHT; row++)
    {
        //Check if row is full
        bool allFull = true;
        for (int col = 0; col < BOARD_WIDTH; col++)
        {
            if (tiles[row][col].getTileType() == TILE_NULL || tiles[row][col].getTileType() == TILE_GHOST)
            {
                allFull = false;
            }
        }
        //If a row is full, remove it and shift all rows above it down
        if (allFull)
        {
            numLines += 1;
            for (int i = 0; i < row - 1; i++)
            {
                tiles[row - i] = tiles[row - i - 1];
            }
        }
    }

    //Fix tile positions
    for (int row = 0; row < BOARD_HEIGHT; row++)
    {
        for (int col = 0; col < BOARD_WIDTH; col++)
        {
            tiles[row][col].setPos(row, col);
        }
    }

    return numLines;
}
