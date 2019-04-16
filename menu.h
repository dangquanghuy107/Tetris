#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include "button.h"

enum windowType{
    GAME,
    TUTORIAL,
    MENU,
};

class Menu{
public:
    Menu();
    ~Menu();
    void renderMenu();
    void getEvent();
    void onStartClick();
    void onTutorialClick();

    int getCurrentWindow(){
        return currentWindow;
    }

    void setCurrentWindow(int newCurrentWindow){
        currentWindow = newCurrentWindow;
    }

private:
    int currentWindow = MENU; /// MENU, TUTORIAL, GAME
    SDL_Texture* backgroundImage;
    Button button[TOTAL_MENU_BUTTON];
    Button backButton;
};

#endif // MENU_H
