#ifndef NUMBER_H
#define NUMBER_H

#include <SDL.h>
#include <SDL_ttf.h>

class Number{
public:
    Number();
    ~Number();
    Number(std::string pathToBoardImage, int maxLength, int x, int y, int w, int h);

    inline int getX() { return posX; }
    inline int getY() { return posY; }
    inline int getW() { return width; }
    inline int getH() { return height; }

    void setAlpha(int alpha);
    void setFontColor(int r, int g, int b);

    void renderBoard();
    void printValue(int value, int x, int y, int w, int h);

private:
    SDL_Texture* numberBoard;
    SDL_Rect boardRect;
    SDL_Rect textRect;
    SDL_Color color;
    TTF_Font* font = TTF_OpenFont("font/advanced_pixel_lcd-7.ttf", 86.17);
    int posX, posY, width, height;
    int maxLength;
};

#endif
