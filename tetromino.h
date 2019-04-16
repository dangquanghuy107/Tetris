#ifndef TETROMINO_H
#define TETROMINO_H

#include <bits/stdc++.h>
#include <SDL.h>

enum {
    O_PIECE,
    T_PIECE,
    I_PIECE,
    Z_PIECE,
    S_PIECE,
    J_PIECE,
    L_PIECE,
    TOTAL_PIECE,
};

enum {
    YELLOW,
    PURPLE,
    CYAN,
    RED,
    GREEN,
    BLUE,
    ORANGE,
    GRID_COLOR,
    TOTAL_COLOR,
};

class Tetromino{
public:
    Tetromino();
    ~Tetromino();
    Tetromino(int _type);

    void rotateRight();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();

    inline int getColor() { return _color; }
    inline int getType() { return _pieceType; }
    inline bool isOddWidth() {return _isOddWidth; }

    inline std::vector<std::pair<int, int>> getCells() { return _cells; }
    inline std::pair<int, int> getCurrentPosition() { return currentPosition; }
    inline std::pair<int, int> getInitialPosition() { return initialPosition; }

private:
    std::vector <std::pair <int, int>> _cells;
    int _pieceType;
    int _color;
    bool _isOddWidth;
    std::pair <int, int> initialPosition;
    std::pair <int, int> currentPosition;
};

#endif // TETROMINO_H
