#include <SDL.h>

#include "header.h"

Button::Button(){}

Button::~Button(){}

Button::Button(std::string defaultSrc, std::string pressedSrc, int x, int y, int w, int h): w(w), h(h){
    position.x = x;
    position.y = y;
    rect = {x, y, w, h};
    defaultButton = window.loadTexture(defaultSrc.c_str());
    pressedButton = window.loadTexture(pressedSrc.c_str());
    currentButton = defaultButton;
}

int Button::handleEvent(SDL_Event* e){
    if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONUP){
        int x, y;
        SDL_GetMouseState( &x, &y );
        if (x >= position.x && x <= position.x + w
         && y >= position.y && y <= position.y + h){
            if (e->type == SDL_MOUSEBUTTONDOWN){
                return PRESSED;
            }
            if (e->type == SDL_MOUSEMOTION){
                currentButton = pressedButton;
                return HOVERED;
            }
         }
         else{
            currentButton = defaultButton;
            return MOVED_OUT;
         }
    }
    return -1;
}

void Button::render(){
    SDL_RenderCopy(_renderer, currentButton, NULL, &rect);
}
