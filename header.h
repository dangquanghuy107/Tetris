#ifndef HEADER_H
#define HEADER_H

#include "window.h"
#include "board.h"
#include "tetromino.h"
#include "game.h"
#include "number.h"
#include "menu.h"
#include "button.h"
#include "effect.h"
#include "sound.h"

using namespace std;


const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

extern Window window;
extern SDL_Window* _window;
extern SDL_Renderer* _renderer;
extern SDL_Texture* _colorTexture[TOTAL_COLOR];
extern SDL_Texture* _ingameTexture;
extern SDL_Texture* menuTexture;
extern SDL_Texture* tutorialTexture;
extern SDL_Texture* gameTexture;
extern SDL_Texture* gameOverTexture;
extern SDL_Texture* countDown[4];

extern SDL_Cursor* handCursor;
extern SDL_Cursor* arrowCursor;

extern Game game;
extern Tetromino _pieces[TOTAL_PIECE];
extern Effect effect;
extern Board board;
extern Game game;
extern Menu mainMenu;
extern Sound sound;

#endif // HEADER_H
