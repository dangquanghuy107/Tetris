#include <SDL.h>
#include "header.h"

SDL_Texture* menuTexture;
SDL_Texture* tutorialTexture;
SDL_Texture* gameTexture;
SDL_Texture* blackTexture;
SDL_Texture* pausedTexture;
Button pauseGameButton[TOTAL_GAME_PAUSE_BUTTON];

void Effect::init(){
    menuTexture = window.loadTexture("image/full-menu.png");
    tutorialTexture = window.loadTexture("image/tutorialpage.png");
    gameTexture = window.loadTexture("image/background3.png");
    blackTexture = window.loadTexture("image/black_texture.png");
    pausedTexture = window.loadTexture("image/paused.png");
    pauseGameButton[CONTINUE] = Button("image/continue.png", "image/pressedcontinue.png", 10 * CELL_SIZE + 15, 10 * CELL_SIZE, LARGE_BUTTON_WIDTH, LARGE_BUTTON_HEIGHT);
    pauseGameButton[BACK_TO_MENU] = Button("image/home.png", "image/pressedhome.png", 10 * CELL_SIZE + 15, 14 * CELL_SIZE, LARGE_BUTTON_WIDTH, LARGE_BUTTON_HEIGHT);;
}

void Effect::fadeIn(SDL_Texture* image){
    SDL_SetTextureBlendMode(image, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);

    for (int _alpha = 0; _alpha <= 255; _alpha += 3){
        window.clearScreen(image);
        SDL_SetTextureAlphaMod(image, _alpha);
        SDL_RenderCopy(_renderer, image, NULL, NULL);
        SDL_RenderPresent(_renderer);
    }
}

void Effect::fadeOut(SDL_Texture* image){
    SDL_SetTextureBlendMode(image, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);

    for (int _alpha = 255; _alpha >= 0; _alpha -= 3){
        window.clearScreen(image);
        SDL_SetTextureAlphaMod(image, _alpha);
        SDL_RenderCopy(_renderer, image, NULL, NULL);
        SDL_RenderPresent(_renderer);
    }
}

void Effect::drawBoard(){
    window.clearScreen(_ingameTexture);
    game.updateLevel();
    game.updateScore();

    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++){
            board.paintCell(i, j);
        }
}

bool Effect::pause(){
    drawBoard();
    SDL_RenderCopy(_renderer, pausedTexture, NULL, NULL);
    SDL_RenderPresent(_renderer);

    SDL_Event event;

    for (int i = 0; i < TOTAL_GAME_PAUSE_BUTTON; i++)
        pauseGameButton[i].setDefaultButton();

    while (1){
        bool pollSuccess = SDL_PollEvent(&event);
        if (pollSuccess){
            bool hover = true;
            if (event.type == SDL_QUIT){
                window.close();
                exit(0);
            }

            for (int i = 0; i < TOTAL_GAME_PAUSE_BUTTON; i++){
                int mouseState = pauseGameButton[i].handleEvent(&event);

                if (mouseState == PRESSED){
                    hover = false;
                    SDL_SetCursor( arrowCursor );
                    if (i == CONTINUE){
                        effect.resume();
                        return false;
                    }
                    else{
                        effect.fadeIn(menuTexture);
                        game.reset();
                        mainMenu.setCurrentWindow(MENU);
                        mainMenu.renderMenu();
                        return true;
                    }
                }
                else
                    if (mouseState == HOVERED) hover = true;

                pauseGameButton[i].render();
            }

            if (hover) SDL_SetCursor( handCursor );
            else SDL_SetCursor( arrowCursor );
        }

        SDL_RenderPresent(_renderer);
    }

    return false;
}

void Effect::resume(){
    int curValue = 3;
    int lastTime = SDL_GetTicks();

    for (;;){
        drawBoard();
        SDL_RenderCopy(_renderer, countDown[curValue], NULL, NULL);
        SDL_RenderPresent(_renderer);

        if (curValue < 1) break;
        if ((int)SDL_GetTicks() > lastTime + 990){
            lastTime += 990;
            curValue--;
        }
    }

    drawBoard();
    game.updateNextField();
    SDL_RenderPresent(_renderer);
}
