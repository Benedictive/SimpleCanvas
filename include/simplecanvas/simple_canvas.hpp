#pragma once

#include <functional>
#include <optional>
#include <vector>

#include <SDL3/SDL.h>

class SimpleCanvas
{
public:
    const unsigned int WINDOW_WIDTH;
    const unsigned int WINDOW_HEIGHT;

private:
    bool running = true;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* sdlTexture = nullptr;

    std::vector<int> screenPixels;

    std::optional<std::function<void(SDL_Event&)>> eventHandler;

public:
    SimpleCanvas(unsigned int winHeight, unsigned int winWidth);
    ~SimpleCanvas();
    void RegisterEventHandler(std::function<void(SDL_Event&)> userfunction);
    //Must be run in the same thread as InitSDL
    void Run(std::function<void(SimpleCanvas*)> userfunction);
    std::vector<int>& GetPixelStore();

private:
    void InitSDL();
    void OnEvent(SDL_Event *event);
    void Loop(std::function<void(SimpleCanvas*)> userfunction);
    void Render();
};