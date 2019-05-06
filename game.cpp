#include <SDL.h>
#include <SDL_ttf.h>
#include "header.h"

Tetromino _pieces[TOTAL_PIECE];
Button gameOverButton[TOTAL_GAME_OVER_BUTTON];

Game::Game(){
    _speed = 800;
    _score = 0;
    _level = 1;
    _deletedRows = 0;
    _holdPiece = -1;
}

void Game::init(){
    board.loadCellTexture();

    for (int i = 0; i < TOTAL_PIECE; i++){
        _pieces[i] = Tetromino(i);
    }

    gameOverButton[PLAY_AGAIN] = Button("image/playagain.png", "image/pressedplayagain.png", 10 * CELL_SIZE + 15, 10 * CELL_SIZE, LARGE_BUTTON_WIDTH, LARGE_BUTTON_HEIGHT);
    gameOverButton[MAIN_MENU] = Button("image/home.png", "image/pressedhome.png", 10 * CELL_SIZE + 15, 14 * CELL_SIZE, LARGE_BUTTON_WIDTH, LARGE_BUTTON_HEIGHT);

    level.setFontColor(255, 0, 52);
    score.setFontColor(255, 0, 52);

    board.init();
    srand(time(NULL));
}

int Game::getRandomPiece(){
    return rand() % TOTAL_PIECE;
}

int Game::getNextPiece(){
    int result = _next[0];
    _next[0] = _next[1];
    _next[1] = _next[2];
    _next[2] = getRandomPiece();
    return result;
}

void Game::updateNextField(){
    for (int i = 0; i < 3; i++)
        board.deletePiece(22 * CELL_SIZE, (4 * i + 3) * CELL_SIZE);
    for (int i = 0; i < 3; i++)
        board.renderPiece(_next[i], 24 * CELL_SIZE, (4 * i + 5) * CELL_SIZE);
}

void Game::removeLines(){
    if (board.needDelete()){
        _deletedRows += board.getDeleteRowCount();

        switch (board.getDeleteRowCount()){
            case 1:
                _score += 40 * _level;
                break;
            case 2:
                _score += 100 * _level;
                break;
            case 3:
                _score += 300 * _level;
                break;
            case 4:
                _score += 1200 * _level;
                break;
            default:
                break;
        }

        if (_deletedRows <= 5) {_level = 1; _speed = 800;}
        else if (_deletedRows <= 10) {_level = 2; _speed = 720;}
        else if (_deletedRows <= 20) {_level = 3; _speed = 630;}
        else if (_deletedRows <= 35) {_level = 4; _speed = 550;}
        else if (_deletedRows <= 55) {_level = 5; _speed = 470;}
        else if (_deletedRows <= 80) {_level = 6; _speed = 380;}
        else if (_deletedRows <= 110) {_level = 7; _speed = 300;}
        else if (_deletedRows <= 145) {_level = 8; _speed = 220;}
        else if (_deletedRows <= 185) {_level = 9; _speed = 130;}
        else if (_deletedRows <= 230) {_level = 10; _speed = 100;}

        board.deleteRows();
    }
}

void Game::updateLevel(){
    int x = level.getX();
    int y = level.getY();
    int w = level.getW();
    int h = level.getH();
    level.renderBoard();
    level.printValue(_level, x + 4, y + 4, w - 2, h - 2);
}

void Game::updateScore(){
    int x = score.getX();
    int y = score.getY();
    int w = score.getW();
    int h = score.getH();
    score.renderBoard();
    score.printValue(_score, x + 4, y + 4, w - 2, h - 2);
}

void Game::renderHoldPiece(){
    board.renderPiece(_holdPiece, 4 * CELL_SIZE, 5 * CELL_SIZE);
}

bool Game::tick(Tetromino curPiece, bool holdUsed){
    while (curPiece.getCurrentPosition().second >= 0 && !board.isValidPosition(curPiece))
        curPiece.moveUp();
    if (board.isValidPosition(curPiece))
        board.renderPiece(curPiece);
    else
        return false;

    int curTick = SDL_GetTicks();
    bool upPressed = false;
    bool hardDrop = false;
    Tetromino newPiece;
    SDL_Event curEvent;

    int startPress = -1;

    while (1){
        int frameStartTime = SDL_GetTicks();
        if ((int)SDL_GetTicks() > curTick + _speed){
            curTick += _speed;

            if (board.canMoveDown(curPiece)){
                board.deletePiece(curPiece);
                curPiece.moveDown();
                board.renderPiece(curPiece);
            }
            else break;
        }

        SDL_PollEvent(&curEvent);
        if (curEvent.type == SDL_QUIT) exit(0);

        newPiece = curPiece;

        const Uint8 *keyState = SDL_GetKeyboardState(NULL);
        if (!keyState[SDL_SCANCODE_UP]) upPressed = false;

        if (!hardDrop && curEvent.type == SDL_KEYDOWN){
                bool firstMove;
                if (startPress == -1) {
                    startPress = SDL_GetTicks();
                    firstMove = true;
                }
                int endPress = SDL_GetTicks();
                int elapsedTime = endPress - startPress;

                switch (curEvent.key.keysym.sym){
                    case SDLK_UP:
                        if (!upPressed) newPiece.rotateRight();
                        upPressed = true;
                        break;
                    case SDLK_DOWN:
                        if (board.canMoveDown(newPiece)){
                            newPiece.moveDown();
                            _score += 2;
                        }
                        updateScore();
                        SDL_Delay(75);
                        break;
                    case SDLK_RIGHT:
                        if (firstMove)
                            newPiece.moveRight();
                        firstMove = false;

                        if (!board.isValidPosition(newPiece)) newPiece = curPiece;

                        board.deletePiece(curPiece);
                        board.renderPiece(newPiece);

                        SDL_RenderPresent(_renderer);

                        if (elapsedTime > 250){
                            newPiece.moveRight();
                            SDL_Delay(75);
                        }
                        break;
                    case SDLK_LEFT:
                        if (firstMove)
                            newPiece.moveLeft();
                        firstMove = false;

                        if (!board.isValidPosition(newPiece)) newPiece = curPiece;

                        board.deletePiece(curPiece);
                        board.renderPiece(newPiece);

                        SDL_RenderPresent(_renderer);

                        if (elapsedTime > 250){
                            newPiece.moveLeft();
                            SDL_Delay(75);
                        }
                        break;
                    case SDLK_SPACE:
                        if (board.canMoveDown(newPiece)){
                            board.hardDrop(newPiece);
                            SDL_Delay(75);
                            _score += 20;
                            updateScore();
                            hardDrop = true;
                        }
                        break;
                    case SDLK_c:
                        if (!holdUsed){
                            if (_holdPiece == -1){
                                _holdPiece = curPiece.getType();

                                board.renderPiece(_holdPiece, 4 * CELL_SIZE, 5 * CELL_SIZE);
                                board.deletePiece(curPiece);

                                newPiece = _pieces[getNextPiece()];

                                updateNextField();
                                tick(newPiece, 1);
                            }
                            else{
                                newPiece = _pieces[_holdPiece];
                                _holdPiece = curPiece.getType();
                                board.deletePiece(2 * CELL_SIZE, 3 * CELL_SIZE);
                                board.renderPiece(_holdPiece, 4 * CELL_SIZE, 5 * CELL_SIZE);
                                board.deletePiece(curPiece);
                                tick(newPiece, 1);
                            }
                            return true;
                        }
                        break;
                    case SDLK_p:{
                        bool isExit = effect.pause();
                        curTick = SDL_GetTicks();
                        if (isExit) return false;
                        break;
                    }
                    default:
                        break;
                }
            }
            else if (curEvent.type == SDL_KEYUP)
                startPress = -1;

        if (!board.isValidPosition(newPiece)) newPiece = curPiece;

        board.deletePiece(curPiece);
        board.renderPiece(newPiece);

        SDL_RenderPresent(_renderer);

        int frameTime = SDL_GetTicks() - frameStartTime;
        if (frameTime < DELAY_TIME) SDL_Delay(DELAY_TIME - frameTime);

        curPiece = newPiece;
    }

    board.putPiece(curPiece);
    removeLines();

    updateLevel();
    updateScore();

    return true;
}

void Game::gameOver(){
    reset();

    SDL_RenderCopy(_renderer, gameOverTexture, NULL, NULL);
    SDL_RenderPresent(_renderer);

    SDL_Event event;

    for (int i = 0; i < TOTAL_GAME_OVER_BUTTON; i++)
        gameOverButton[i].setDefaultButton();

    /// Handle buttons events
    while (1){
        bool pollSuccess = SDL_PollEvent(&event);
        if (pollSuccess){
            bool hover = false;
            if (event.type == SDL_QUIT){
                window.close();
                return;
            }

            for (int i = 0; i < TOTAL_GAME_OVER_BUTTON; i++){
                int mouseState = gameOverButton[i].handleEvent(&event);

                if (mouseState == PRESSED){
                    hover = false;
                    SDL_SetCursor( arrowCursor );

                    if (i == PLAY_AGAIN){
                        effect.resume();
                        game.newGame();
                    }
                    else{
                        effect.fadeIn(menuTexture);
                    }

                    return;
                }
                else if (mouseState == HOVERED)
                    hover = true;

                gameOverButton[i].render();
            }

            if (hover) SDL_SetCursor( handCursor );
            else SDL_SetCursor( arrowCursor );
        }

        SDL_RenderPresent(_renderer);
    }
}

void Game::reset(){
    _speed = 800;
    _score = 0;
    _level = 1;
    _deletedRows = 0;
    _holdPiece = -1;
    isGameOver = false;
    board.init();
}

void Game::newGame(){
    reset();

    for (int i = 0; i < 3; i++){
        _next[i] = getRandomPiece();
        board.renderPiece(_next[i], 24 * CELL_SIZE, (4 * i + 5) * CELL_SIZE);
    }

    updateLevel();
    updateScore();
    while (!isGameOver){
        Tetromino nextPiece = getNextPiece();

        updateNextField();

        SDL_RenderPresent(_renderer);

        isGameOver = !tick(nextPiece, 0);
    }

    if (mainMenu.getCurrentWindow() == GAME)
        gameOver();
}

