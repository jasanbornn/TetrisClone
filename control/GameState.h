//
// Created by jamie on 11/13/22.
//

#ifndef TETRISCLONE_GAMESTATE_H
#define TETRISCLONE_GAMESTATE_H


#include "../model/Board.h"
#include "../model/piece/Piece.h"
#include "../model/piece/OPiece.h"
#include "../model/piece/LPiece.h"
#include "../model/piece/TPiece.h"
#include "../model/piece/JPiece.h"
#include "../model/piece/IPiece.h"
#include "../model/piece/SPiece.h"
#include "../model/piece/ZPiece.h"
#include "../model/Bag.h"
#include "GhostPiece.h"
#include "../model/Holder.h"
#include "../input/Input.h"

#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameState
{

    sf::RenderWindow* pWindow;

    sf::Clock clock;
    sf::Time time;
    Bag bag;

    std::shared_ptr<GhostPiece> pGhostPiece;
    std::shared_ptr<Board> pBoard;
    std::shared_ptr<Piece> pPiece;
    std::shared_ptr<Holder> pHolder;

    bool canHoldPiece;

    void tryRotateIPieceLeft();
    void tryRotateIPieceRight();

public:

    explicit GameState(sf::RenderWindow* pWindow);

    void update(Input input);

    void processInputs(const Input& input);

    void setBoardState(std::shared_ptr<Board> pBoard);
    void setBoardState(Board board);

    std::shared_ptr<Board> getBoardState();
    std::shared_ptr<Piece> getPieceState();
    std::shared_ptr<GhostPiece> getGhostPieceState();
    std::shared_ptr<Holder> getHolderState();

    void setPieceState(std::shared_ptr<Piece> pPiece);
    void spawnNewPiece();

    bool pieceCanMove(int dRow, int dCol);

    void movePieceLeft();
    void movePieceRight();
    void movePieceUp();
    void movePieceDown();

    void placePiece();
    void dropPiece();

    bool pieceCollides();

    void tryRotatePieceLeft();
    void tryRotatePieceRight();

    void updateGhostPiece();

    void holdPiece();

};


#endif //TETRISCLONE_GAMESTATE_H
