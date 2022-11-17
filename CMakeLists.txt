cmake_minimum_required(VERSION 3.22)
project(TetrisClone)

set(CMAKE_CXX_STANDARD 14)

add_executable(TetrisClone main.cpp input/InputHandler.cpp input/InputHandler.h render/Renderer.cpp render/Renderer.h input/Input.cpp input/Input.h model/control/Updater.cpp model/control/Updater.h model/control/GameState.cpp model/control/GameState.h model/board/Board.cpp model/board/Board.h model/piece/Piece.cpp model/piece/Piece.h WindowConstants.h model/piece/OPiece.cpp model/piece/OPiece.h model/piece/LPiece.cpp model/piece/LPiece.h model/piece/Tile.cpp model/piece/Tile.h model/piece/JPiece.cpp model/piece/JPiece.h model/piece/ZPiece.cpp model/piece/ZPiece.h model/piece/IPiece.cpp model/piece/IPiece.h model/piece/SPiece.cpp model/piece/SPiece.h model/piece/TPiece.cpp model/piece/TPiece.h)

target_link_libraries(TetrisClone sfml-graphics)
target_link_libraries(TetrisClone sfml-window)
target_link_libraries(TetrisClone sfml-system)
