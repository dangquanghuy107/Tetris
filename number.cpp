#include <SDL.h>
#include <SDL_ttf.h>

#include "header.h"

Number::Number(){}

Number::~Number(){
    SDL_DestroyTexture(numberBoard);
    TTF_CloseFont(font);
    font = nullptr;
}

Number::Number(std::string pathToBoardImage, int maxLength, int x, int y, int w, int h)
    :posX(x), posY(y), width(w), height(h), maxLength(maxLength){

        numberBoard = window.loadTexture(pathToBoardImage.c_str());
        boardRect = {x, y, w, h};

        if (font == nullptr)
            std::cout << TTF_GetError() << std::endl;
    }

void Number::renderBoard(){
    SDL_RenderCopy(_renderer, numberBoard, NULL, &boardRect);
}

void Number::setAlpha(int alpha){
    SDL_SetTextureBlendMode(numberBoard, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(numberBoard, alpha);
}

void Number::setFontColor(int r, int g, int b){
    color = {(Uint8)r, (Uint8)g, (Uint8)b};
}

void Number::printValue(int value, int x, int y, int w, int h){
    textRect = {x, y, w, h};
    std::stringstream ss;
    ss << value;
    std::string stringValue = ss.str();
    while ((int)stringValue.size() < maxLength) stringValue = '0' + stringValue;

    SDL_Surface* stringSurface = TTF_RenderText_Solid(font, stringValue.c_str(), color);
    SDL_Texture* stringTexture = SDL_CreateTextureFromSurface(_renderer, stringSurface);

    SDL_RenderCopy(_renderer, stringTexture, NULL, &textRect);

    /// dellocate the memory

    SDL_DestroyTexture(stringTexture);
    SDL_FreeSurface(stringSurface);
    stringTexture = nullptr;
    stringSurface = nullptr;
}
