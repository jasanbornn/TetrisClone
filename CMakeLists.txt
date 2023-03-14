cmake_minimum_required(VERSION 3.22)
project(TetrisClone)

set(CMAKE_CXX_STANDARD 14)

add_executable(TetrisClone main.cpp input/InputHandler.cpp input/InputHandler.h render/Renderer.cpp render/Renderer.h input/Input.cpp input/Input.h control/GameState.cpp control/GameState.h model/Board.cpp model/Board.h model/piece/Piece.cpp model/piece/Piece.h WindowConstants.h model/piece/OPiece.cpp model/piece/OPiece.h model/piece/LPiece.cpp model/piece/LPiece.h model/Tile.cpp model/Tile.h model/piece/JPiece.cpp model/piece/JPiece.h model/piece/ZPiece.cpp model/piece/ZPiece.h model/piece/IPiece.cpp model/piece/IPiece.h model/piece/SPiece.cpp model/piece/SPiece.h model/piece/TPiece.cpp model/piece/TPiece.h model/Bag.cpp model/Bag.h control/GhostPiece.cpp control/GhostPiece.h model/Holder.cpp model/Holder.h model/Menu.cpp model/Menu.h)

target_link_libraries(TetrisClone sfml-graphics)
target_link_libraries(TetrisClone sfml-window)
target_link_libraries(TetrisClone sfml-system)
