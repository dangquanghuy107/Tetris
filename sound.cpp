#include <SDL_mixer.h>

#include "header.h"

Sound::Sound(){
    _song[THEME_SONG] = loadMusic("sound/theme-song.mp3");
    _song[GAME_OVER_SONG] = loadMusic("sound/gameover.wav");

    _sound[CLEAR_SOUND] = loadChunk("sound/line.wav");
    _sound[CLEAR_FOUR_SOUND] = loadChunk("sound/clear.wav");
    _sound[FALL_SOUND] = loadChunk("sound/fall.wav");
}

Sound::~Sound(){
    for (int i = 0; i < TOTAL_SOUND; i++){
        Mix_FreeChunk(_sound[i]);
        _sound[i] = NULL;
    }

    for (int i = 0; i < TOTAL_SONG; i++){
        Mix_FreeMusic(_song[i]);
        _song[i] = NULL;
    }

}

Mix_Music* Sound::loadMusic(std::string src){
    Mix_Music* result = Mix_LoadMUS(src.c_str());

    if (result == NULL)
        std::cerr << "Unable to load Music " << src << endl;

    return result;
}

Mix_Chunk* Sound::loadChunk(std::string src){
    Mix_Chunk* result = Mix_LoadWAV(src.c_str());

    if (result == NULL)
        std::cerr << "Unable to load Chunk " << src << endl;

    return result;
}
