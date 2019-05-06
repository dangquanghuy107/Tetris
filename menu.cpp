#include <SDL.h>

#include "header.h"

Effect effect;
SDL_Texture* _ingameTexture;
SDL_Texture* gameOverTexture;
SDL_Texture* countDown[4];
SDL_Cursor* handCursor;
SDL_Cursor* arrowCursor;
SDL_Event event;
//
Menu::Menu(){
    effect.init();
    _ingameTexture = window.loadTexture("image/background.png");
    backgroundImage = window.loadTexture("image/menu.png");
    gameOverTexture = window.loadTexture("image/gameover.png");

    countDown[1] = window.loadTexture("image/1.png");
    countDown[2] = window.loadTexture("image/2.png");
    countDown[3] = window.loadTexture("image/3.png");

    backButton = Button("image/backbutton.png", "image/pressedbackbutton.png", 27 * CELL_SIZE, 20 * CELL_SIZE, 2 * CELL_SIZE, 1 * CELL_SIZE);
    button[START_BUTTON] = Button("image/start.png", "image/pressedstart.png", 10 * CELL_SIZE + 15, 9 * CELL_SIZE, LARGE_BUTTON_WIDTH, LARGE_BUTTON_HEIGHT);
    button[TUTORIAL_BUTTON] = Button("image/tutorial.png", "image/pressedtutorial.png", 10 * CELL_SIZE + 15, 13 * CELL_SIZE, LARGE_BUTTON_WIDTH, LARGE_BUTTON_HEIGHT);
    button[EXIT_BUTTON] = Button("image/exit.png", "image/pressedexit.png", 10 * CELL_SIZE + 15, 17 * CELL_SIZE, LARGE_BUTTON_WIDTH, LARGE_BUTTON_HEIGHT);

    handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    arrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
}

Menu::~Menu(){
    SDL_DestroyTexture(backgroundImage);
}

void Menu::renderMenu(){
    window.clearScreen(backgroundImage);
    for (int i = 0; i < TOTAL_MENU_BUTTON; i++){
        button[i].render();
    }
    SDL_RenderPresent(_renderer);
}

void Menu::onStartClick(){
    currentWindow = GAME;

    effect.fadeOut(menuTexture);
    effect.fadeIn(gameTexture);

    effect.resume();

    game.newGame();

    currentWindow = MENU;
    renderMenu();
}

void Menu::onTutorialClick(){
    currentWindow = TUTORIAL;
    effect.fadeOut(menuTexture);
    effect.fadeIn(tutorialTexture);

    backButton.setDefaultButton();

    backButton.render();

    SDL_Event e;

    while (1){
        bool pollSuccess = SDL_PollEvent(&e);
        if (pollSuccess){
            if (e.type == SDL_QUIT){
                window.close();
                return;
            }

            bool hover = false;
            int mouseState = backButton.handleEvent(&e);
            if (mouseState == PRESSED){
                SDL_SetCursor( arrowCursor );
                hover = false;

                effect.fadeOut(tutorialTexture);
                effect.fadeIn(menuTexture);

                currentWindow = MENU;
                renderMenu();
                return;
            }
            else if (mouseState == HOVERED)
                hover = true;

            if (hover) SDL_SetCursor( handCursor );
            else SDL_SetCursor( arrowCursor );
            backButton.render();
        }
        SDL_RenderPresent(_renderer);
    }

}

void Menu::getEvent(){
    if (currentWindow != MENU) return;

    while (SDL_PollEvent(&event) != 0){
        if (event.type == SDL_QUIT){
            window.close();
            break;
        }

        bool hover = false;

        for (int i = 0; i < TOTAL_MENU_BUTTON; i++){
            int mouseState = button[i].handleEvent(&event);
            if (mouseState == PRESSED){
                SDL_SetCursor(arrowCursor);
                hover = false;
                switch (i){
                    case START_BUTTON:
                        onStartClick();
                        return;
                        break;

                    case TUTORIAL_BUTTON:
                        onTutorialClick();
                        return;
                        break;

                    case EXIT_BUTTON:
                        effect.fadeOut(menuTexture);
                        window.close();
                        return;
                        break;

                    default:
                        break;
                }
            }
            else{
                button[i].render();
                if (mouseState == HOVERED) hover = true;
            }
        }
        if (hover) SDL_SetCursor(handCursor);
        else SDL_SetCursor(arrowCursor);

        SDL_RenderPresent(_renderer);
    }
}
