#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>

const int LARGE_BUTTON_WIDTH = 270;
const int LARGE_BUTTON_HEIGHT = 90;

enum {
    START_BUTTON,
    TUTORIAL_BUTTON,
    EXIT_BUTTON,
    TOTAL_MENU_BUTTON,
};

enum{
    HOVERED,
    PRESSED,
    MOVED_OUT,
    TOTAL_MOUSE_STATE,
};

class Button{
public:
    Button();
    ~Button();

    Button(std::string defaultSrc, std::string pressedSrc, int x, int y, int w, int h);

    int handleEvent(SDL_Event* e);

    void setDefaultButton(){
        currentButton = defaultButton;
    }

    void render();

private:
    SDL_Point position; /// x, y coordinate
    int w, h;
    SDL_Texture* defaultButton;
    SDL_Texture* pressedButton;
    SDL_Texture* currentButton;
    SDL_Rect rect;
};

#endif // BUTTON_H
