#ifndef BOARD_H
#define BOARD_H

#include <SDL.h>
#include "tetromino.h"

const int BOARD_WIDTH = 10; /// 0-indexed
const int BOARD_HEIGHT = 20; /// 0-indexed
const int CELL_SIZE = 30;

class Board{
public:
    Board();
    ~Board();

    void init();

    /// render a cell using brick texture
    void paintCell(SDL_Rect &rect, int color);
    void paintCell(int x, int y);

    void loadCellTexture();

    /// delete pieces on game board
    void deletePiece(Tetromino piece);

    /// delete pieces on next/ hold panel
    void deletePiece(int x, int y);

    /// render pieces on game board
    void renderPiece(Tetromino piece);

    /// render pieces on next/ hold panel
    void renderPiece(int pieceType, int x, int y);

    /// settle pieces that finished dropping
    void putPiece(Tetromino piece);

    /// hard drop a piece (SPACE)
    void hardDrop(Tetromino &piece);

    /// delete full rows
    void deleteRows();

    bool canMoveDown(Tetromino piece);
    bool isValidPosition(Tetromino piece);

    bool needDelete() {
        return _deleteRowCount > 0;
    }

    int getDeleteRowCount() {
        return _deleteRowCount;
    }

private:
    int _grid[BOARD_WIDTH][BOARD_HEIGHT + 1]; /// color of cell
    SDL_Rect _rects[BOARD_WIDTH][BOARD_HEIGHT + 1]; /// SDL_Rect representing cell

    int _totalRow[BOARD_HEIGHT];  /// number of filled cells in a row
    int _deleteRowCount;
    bool _deleteRow[BOARD_HEIGHT];
};

#endif
