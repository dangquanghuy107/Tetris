#include <bits/stdc++.h>
#include "header.h"

using namespace std;

Window window = Window("Tetris", 900, 660);
SDL_Window* _window = nullptr;
SDL_Renderer* _renderer = nullptr;
Board board;
Game game;
Menu mainMenu;

int main(int argc, char *argv[]){
    game.init();
    effect.fadeIn(menuTexture);
    mainMenu.renderMenu();

    while (!window.isClosed()){
        mainMenu.getEvent();
    }
    return 0;
}
