#include <SDL.h>
#include <iostream>
#include "header.h"

SDL_Texture* _colorTexture[TOTAL_COLOR];

Board::Board(){}
Board::~Board(){}

void Board::init(){
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++){
            _rects[i][j] = {30 * 10 + i * (CELL_SIZE), 30 + j * (CELL_SIZE), CELL_SIZE, CELL_SIZE};
            _grid[i][j] = GRID_COLOR;
        }

    memset(_totalRow, 0, sizeof(_totalRow));
    _deleteRowCount = 0;
    memset(_deleteRow, 0, sizeof(_deleteRow));
}

void Board::loadCellTexture(){
    _colorTexture[YELLOW] = window.loadTexture("image/yellowbrick.png");
    _colorTexture[RED] = window.loadTexture("image/coralbrick.png");
    _colorTexture[PURPLE] = window.loadTexture("image/pinkbrick.png");
    _colorTexture[ORANGE] = window.loadTexture("image/orangebrick.png");
    _colorTexture[GREEN] = window.loadTexture("image/greenbrick.png");
    _colorTexture[GRID_COLOR] = window.loadTexture("image/darkbrick.png");
    _colorTexture[CYAN] = window.loadTexture("image/lightbluebrick.png");
    _colorTexture[BLUE] = window.loadTexture("image/bluebrick.png");
}

void Board::paintCell(SDL_Rect &rect, int color){
    SDL_RenderCopy(_renderer, _colorTexture[color], NULL, &rect);
}

void Board::paintCell(int x, int y){
    paintCell(_rects[x][y], _grid[x][y]);
}

void Board::deletePiece(Tetromino piece){
    std::pair <int, int> curPosition = piece.getCurrentPosition();
    std::vector <std::pair<int, int>> cells = piece.getCells();

    for (int i = 0; i < (int)cells.size(); i++){
        int row = curPosition.first + cells[i].first;
        int col = curPosition.second + cells[i].second;
        paintCell(_rects[row][col], GRID_COLOR);
    }
}

void Board::renderPiece(Tetromino piece){
    std::pair <int, int> curPosition = piece.getCurrentPosition();
    std::vector <std::pair<int, int>> cells = piece.getCells();

    for (int i = 0; i < (int)cells.size(); i++){
        int row = curPosition.first + cells[i].first;
        int col = curPosition.second + cells[i].second;
        paintCell(_rects[row][col], piece.getColor());
    }
}

/// Delete pieces on next/ hold panel
void Board::deletePiece(int x, int y){
    SDL_Rect newRect = {x, y, 6 * CELL_SIZE, 4 * CELL_SIZE};
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(_renderer, &newRect);
}


/// Render pieces on next/ hold panel
void Board::renderPiece(int pieceType, int x, int y){
    Tetromino curPiece = _pieces[pieceType];

    if (curPiece.isOddWidth()) x += CELL_SIZE / 2;

    std::vector <std::pair<int, int>> cells = curPiece.getCells();
    SDL_Rect newRect;

    for (int i = 0; i < (int)cells.size(); i++){
        int X, Y;
        X = x + cells[i].first * CELL_SIZE;
        Y = y + cells[i].second * CELL_SIZE;
        newRect = {X, Y, CELL_SIZE, CELL_SIZE};
        paintCell(newRect, curPiece.getColor());
    }
}

bool Board::canMoveDown(Tetromino piece){
    std::pair <int, int> curPosition = piece.getCurrentPosition();
    std::vector <std::pair<int, int>> cells = piece.getCells();

    for (int i = 0; i < (int)cells.size(); i++){
        int row = curPosition.first + cells[i].first;
        int col = curPosition.second + cells[i].second + 1;
        if (col == BOARD_HEIGHT) return false;
        if (_grid[row][col] != GRID_COLOR) return false;
    }

    return true;
}

bool Board::isValidPosition(Tetromino piece){
    std::pair <int, int> curPosition = piece.getCurrentPosition();
    if (curPosition.second < 0) return false;

    std::vector <std::pair<int, int>> cells = piece.getCells();

    for (int i = 0; i < (int)cells.size(); i++){
        int row = curPosition.first + cells[i].first;
        int col = curPosition.second + cells[i].second;
        if (row < 0 || row >= BOARD_WIDTH || col >= BOARD_HEIGHT) return false;
        if (_grid[row][col] != GRID_COLOR) return false;
    }

    return true;
}

void Board::putPiece(Tetromino piece){
    int color = piece.getColor();

    std::pair <int, int> curPosition = piece.getCurrentPosition();
    std::vector <std::pair<int, int>> cells = piece.getCells();

    for (int i = 0; i < (int)cells.size(); i++){
        int row = curPosition.first + cells[i].first;
        int col = curPosition.second + cells[i].second;
        _grid[row][col] = color;

        if (++_totalRow[col] == BOARD_WIDTH) {
            _deleteRowCount++;
            _deleteRow[col] = true;
        }
    }
}

void Board::hardDrop(Tetromino &piece){
    while (canMoveDown(piece))
        piece.moveDown();
}

void Board::deleteRows(){
    for (int row = 0; row < BOARD_HEIGHT; row++)
        if (_deleteRow[row]){
            for (int nxtRow = row; nxtRow > 0; nxtRow--){
                for (int col = 0; col < BOARD_WIDTH; col++)
                    _grid[col][nxtRow] =  (nxtRow) ? _grid[col][nxtRow - 1] : -1;
                    _totalRow[nxtRow] = (nxtRow) ? _totalRow[nxtRow - 1] : 0;
            }
            _deleteRow[row] = false;
        }

    _deleteRowCount = 0;

    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++)
            if (_grid[i][j] != GRID_COLOR)
                paintCell(_rects[i][j], _grid[i][j]);
            else
                paintCell(_rects[i][j], GRID_COLOR);
}


