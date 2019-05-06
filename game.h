#ifndef GAME_H
#define GAME_H

#include "number.h"

enum{
    PLAY_AGAIN,
    MAIN_MENU,
    TOTAL_GAME_OVER_BUTTON,
};

struct Game{
public:
    Game();

    void init();
    void newGame();
    void gameOver();

    /// Render the next panel
    void updateNextField();
    void renderHoldPiece();

    /// Remove full lines + update score & level
    void removeLines();

    void updateScore();
    void updateLevel();

    /// Reset game
    void reset();

    int getRandomPiece();
    int getNextPiece();

    /// return true if curPiece can spawn in the board
    /// holdUsed = return true if Hold is used recently
    bool tick(Tetromino curPiece, bool holdUsed);

private:
    int _next[3]; /// next 3 pieces
    bool isGameOver = 0;
    int _speed = 800;
    int _score = 100;
    int _level = 0;
    int _deletedRows = 0;
    int _holdPiece = -1;
    Number score = Number("image/scoreboard.png", 6, 2 * CELL_SIZE - 1, 11 * CELL_SIZE + 14, 6 * CELL_SIZE + 2, CELL_SIZE + 15 + 2);
    Number level = Number("image/levelboard.png", 3, 3 * CELL_SIZE + 14, 17 * CELL_SIZE + 13, 3 * CELL_SIZE + 2, CELL_SIZE + 15 + 3);
};

#endif
