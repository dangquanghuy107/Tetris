#ifndef EFFECT_H
#define EFFECT_H

enum {
    CONTINUE,
    BACK_TO_MENU,
    TOTAL_GAME_PAUSE_BUTTON,
};

class Effect{
public:
    void init();

    /// fade in effect to 'image'
    void fadeIn(SDL_Texture* image);

    /// fade out effect from 'image'
    void fadeOut(SDL_Texture* image);

    /// draw current game status including score, level, next/ hold panel, gameboard
    void drawBoard();

    /// return true if exit button is pressed and vice versa
    bool pause();

    /// tick 3sec before resuming
    void resume();
};

#endif // EFFECT_H
