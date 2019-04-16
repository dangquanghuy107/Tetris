#include <SDL.h>
#include "header.h"

Tetromino::Tetromino(){}

Tetromino::~Tetromino(){
    _cells.clear();
}

Tetromino::Tetromino(int _type): _pieceType(_type), _color(_type){
    switch (_type){
        case O_PIECE:
            _isOddWidth = false;
            initialPosition = std::pair <int, int>(4, 1);
            _cells.emplace_back(0,  0); ///....XX....
            _cells.emplace_back(0, -1); ///....OX....
            _cells.emplace_back(1, -1); ///..........
            _cells.emplace_back(1,  0); ///..........
            break;
        case T_PIECE:
            _isOddWidth = true;
            initialPosition = std::pair <int, int>(4, 1);
            _cells.emplace_back( 0,  0); ///....X.....
            _cells.emplace_back( 0, -1); ///...XOX....
            _cells.emplace_back(-1,  0); ///..........
            _cells.emplace_back( 1,  0); ///..........
            break;
        case I_PIECE:
            _isOddWidth = false;
            initialPosition = std::pair <int, int>(4, 1);
            _cells.emplace_back( 0,  0); ///..........
            _cells.emplace_back(-1,  0); ///...XOXX...
            _cells.emplace_back( 1,  0); ///..........
            _cells.emplace_back( 2,  0); ///..........
            break;
        case Z_PIECE:
            _isOddWidth = true;
            initialPosition = std::pair <int, int>(4, 1);
            _cells.emplace_back( 0,  0); ///...XX.....
            _cells.emplace_back( 0, -1); ///....OX....
            _cells.emplace_back(-1, -1); ///..........
            _cells.emplace_back( 1,  0); ///..........
            break;
        case S_PIECE:
            _isOddWidth = true;
            initialPosition = std::pair <int, int>(4, 1);
            _cells.emplace_back( 0,  0); ///....XX....
            _cells.emplace_back(-1,  0); ///...XO.....
            _cells.emplace_back( 1, -1); ///..........
            _cells.emplace_back( 0, -1); ///..........
            break;
        case J_PIECE:
            _isOddWidth = true;
            initialPosition = std::pair <int, int>(4, 1);
            _cells.emplace_back( 0,  0); ///...X......
            _cells.emplace_back(-1,  0); ///...XOX....
            _cells.emplace_back(-1, -1); ///..........
            _cells.emplace_back( 1,  0); ///..........
            break;
        case L_PIECE:
            _isOddWidth = true;
            initialPosition = std::pair <int, int>(4, 1);
            _cells.emplace_back( 0,  0); ///.....X....
            _cells.emplace_back(-1,  0); ///...XOX....
            _cells.emplace_back( 1,  0); ///..........
            _cells.emplace_back( 1, -1); ///..........
            break;
        default:
            break;
    }

    currentPosition = initialPosition;
}

void Tetromino::rotateRight(){
    if (_pieceType == O_PIECE) return;

    int nSize = (int)_cells.size();

    for (int i = 0; i < nSize; i++){
        std::pair <int, int> temp;
        temp.first = -_cells[i].second;/// 2D rotation formula x = -y
        temp.second = _cells[i].first; /// 90-degree           y = x
        _cells[i] = temp;
    }

    /// I_PIECE special formula
    if (_pieceType == I_PIECE){
        for (int i = 0; i < nSize; i++){
            if (_cells[i].first == -2){
                for (int j = 0; j < nSize; j++)
                    _cells[j].first++;
                break;
            }
            if (_cells[i].second == -2){
                for (int j = 0; j < nSize; j++)
                    _cells[j].second++;
                break;
            }
        }
    }

    /// Wall kick case
    ///  |..........|
    /// X|XXX.......|
    ///  |..........|
    int minX = 0;
    int maxX = BOARD_WIDTH - 1;
    for (int i = 0; i < nSize; i++){
        int curX = _cells[i].first + currentPosition.first;
        if (curX < minX) minX = curX;
        if (curX > maxX) maxX = curX;
    }
    currentPosition.first += -minX;
    currentPosition.first += (BOARD_WIDTH - 1) - maxX;
}

void Tetromino::moveLeft(){
    currentPosition.first--;
}

void Tetromino::moveRight(){
    currentPosition.first++;
}

void Tetromino::moveDown(){
    currentPosition.second++;
}

void Tetromino::moveUp(){
    currentPosition.second--;
}


