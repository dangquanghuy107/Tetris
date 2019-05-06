#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>

enum{
    THEME_SONG,
    GAME_OVER_SONG,
    TOTAL_SONG,
};

enum{
    CLEAR_SOUND,
    CLEAR_FOUR_SOUND,
    FALL_SOUND,
    TOTAL_SOUND,
};

class Sound{
public:
    Sound();
    ~Sound();

    Mix_Music* loadMusic(std::string src);
    Mix_Chunk* loadChunk(std::string src);

    void playMusic(int songID){
        int repeatCount = -1; /// infinity loop
        if (songID == GAME_OVER_SONG)
            repeatCount = 1;

        Mix_PlayMusic(_song[songID], repeatCount);
    }

    void playSound(int soundID){
        Mix_PlayChannel(-1, _sound[soundID], 0);
    }

    void stopMusic(){
        if (Mix_PlayingMusic())
            Mix_HaltMusic();
    }

private:
    Mix_Music* _song[TOTAL_SONG];
    Mix_Chunk* _sound[TOTAL_SOUND];
};

#endif //SOUND_H
