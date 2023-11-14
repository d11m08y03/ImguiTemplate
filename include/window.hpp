#include "imgui.h"
#include <SDL2/SDL.h>
#include <iostream>

class Window {
public:
    Window();
    void run(ImGuiIO& io);
    ~Window();
    void initImgui(ImGuiIO& io);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    void initSDL();
};

