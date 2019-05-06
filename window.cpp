#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "header.h"

Window::Window(const std::string &title, int width, int height): _title(title), _width(width), _height(height){
    _closed = !init();
}

Window::~Window(){
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    _renderer = nullptr;
    _window = nullptr;

    Mix_Quit();
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}

bool Window::init(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cerr << "Failed to initialize SDL.\n";
        return false;
    }

    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) == -1){
        std::cerr << "Failed to initialize Media.\n";
        return false;
    }

    _window = SDL_CreateWindow(
        _title.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        _width, _height,
        SDL_WINDOW_SHOWN);

    if (_window == nullptr){
        std::cerr << "Failed to initialize Window.\n";
        return false;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == nullptr){
        std::cerr << "Failed to initialize Renderer.\n";
        return false;
    }

    int imgFlag = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlag) & imgFlag)){
        std::cerr << "Failed to initialize SDL_Image.\n";
        return false;
    }

    if ( TTF_Init() == -1){
        std::cerr << "Failed to initialize SDL_TTF.\n";
        return false;
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) == -1 ){
        std::cerr << "Failed to initialize SDL_Mixer.\n";
        return false;
    }
    return true;
}

void Window::clearScreen(SDL_Texture* texture){
    SDL_RenderClear(_renderer);
    SDL_RenderCopy(_renderer, texture, NULL, NULL);
}

SDL_Texture* Window::loadTexture(std::string path){
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ){
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else{
        newTexture = SDL_CreateTextureFromSurface( _renderer, loadedSurface );
        if( newTexture == NULL ){
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface( loadedSurface );
        loadedSurface = NULL;
    }

    return newTexture;
}

void Window::close(){
    _closed = true;
}

