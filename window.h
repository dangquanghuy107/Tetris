#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <SDL.h>

class Window{
public:
    Window();
    Window(const std::string &title, int width, int height);
    ~Window();

    void clearScreen(SDL_Texture* texture);
    SDL_Texture* loadTexture(std::string path);
    void close();

    inline bool isClosed() const {
        return _closed;
    }

private:
    bool init();

private:
    std::string _title;
    int _width;
    int _height;

    bool _closed = false;
};

#endif // WINDOW_H
