//
// Created by jamie on 11/13/22.
//

#include <iostream>
#include "Piece.h"


Piece::Piece(int xPos, int yPos)
{
    this->rotation = ROT_ZERO;
}


//    for (int i = 0; i < BOARD_HEIGHT; i++)
//    {
//        for (int j = 0; j < BOARD_WIDTH; j++)
//        {
//            setData(TILE_NULL, i, j);
//        }
//    }
//
//    switch (pieceType)
//    {
//        case PIECE_I:
//            setData(TILE_CYAN, 20, 3);
//            setData(TILE_CYAN, 20, 4);
//            setData(TILE_CYAN, 20, 5);
//            setData(TILE_CYAN, 20, 6);
//            break;
//        case PIECE_J:
//            setData(TILE_BLUE, 20, 4);
//            setData(TILE_BLUE, 21, 4);
//            setData(TILE_BLUE, 21, 5);
//            setData(TILE_BLUE, 21, 6);
//            break;
//        case PIECE_L:
//            setData(TILE_ORANGE, 20, 6);
//            setData(TILE_ORANGE, 21, 4);
//            setData(TILE_ORANGE, 21, 5);
//            setData(TILE_ORANGE, 21, 6);
//            break;
//        case PIECE_O:
//            setData(TILE_YELLOW, 20, 4);
//            setData(TILE_YELLOW, 20, 5);
//            setData(TILE_YELLOW, 21, 4);
//            setData(TILE_YELLOW, 21, 5);
//            break;
//        case PIECE_S:
//            setData(TILE_GREEN, 20, 5);
//            setData(TILE_GREEN, 20, 6);
//            setData(TILE_GREEN, 21, 4);
//            setData(TILE_GREEN, 21, 5);
//            break;
//        case PIECE_Z:
//            setData(TILE_RED, 20, 4);
//            setData(TILE_RED, 20, 5);
//            setData(TILE_RED, 21, 5);
//            setData(TILE_RED, 21, 6);
//            break;
//        case PIECE_T:
//            setData(TILE_PURPLE, 20, 5);
//            setData(TILE_PURPLE, 21, 4);
//            setData(TILE_PURPLE, 21, 5);
//            setData(TILE_PURPLE, 21, 6);
//            break;
//    }


void Piece::moveUp()
{

}

void Piece::moveDown()
{
    if (canMoveTo(1, 0))
    {
        for (auto& tile: tiles)
        {
            tile.move(1, 0);
        }
    }
}

void Piece::moveLeft()
{
    if (canMoveTo(0, -1))
    {
        for (auto& tile: tiles)
        {
            tile.move(0, -1);
        }
    }
}

void Piece::moveRight()
{
    if (canMoveTo(0, 1))
    {
        for (auto& tile: tiles)
        {
            tile.move(0, 1);
        }
    }
}

bool Piece::canMoveTo(int dRow, int dCol)
{

    //4 tiles per piece
    for (int i = 0; i < TILES_PER_PIECE; i++)
    {
        if (tiles[i].getCol() + dCol > BOARD_WIDTH - 1 || tiles[i].getCol() + dCol < 0)
        {
            return false;
        }

        if (tiles[i].getRow() + dRow > BOARD_HEIGHT - 1 || tiles[i].getRow() + dRow < 0)
        {
            return false;
        }

    }
    return true;
}

std::array<Tile, TILES_PER_PIECE>& Piece::getTiles()
{
    return this->tiles;
}

