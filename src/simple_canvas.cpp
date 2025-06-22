#include "simplecanvas/simple_canvas.hpp"

#include <stdexcept>
#include <iostream>

SimpleCanvas::SimpleCanvas(unsigned int winHeight, unsigned int winWidth)
    : WINDOW_HEIGHT(winHeight), WINDOW_WIDTH(winWidth), screenPixels(WINDOW_HEIGHT * WINDOW_WIDTH)
{
    InitSDL();
    sdlTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
}

SimpleCanvas::~SimpleCanvas()
{
    if (sdlTexture) {
        SDL_DestroyTexture(sdlTexture);
    }

    if(renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
	}

	if(window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	SDL_Quit();
}

void SimpleCanvas::RegisterEventHandler(std::function<void(SDL_Event &)> userfunction)
{
	eventHandler = userfunction;
}

void SimpleCanvas::InitSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) == false) {
        std::string errorText = std::string("Unable to Init SDL: ") + SDL_GetError();
        throw std::runtime_error(errorText);
	}

	if((window = SDL_CreateWindow("Simplescreendrawer",WINDOW_WIDTH, WINDOW_HEIGHT, 0)) == NULL) {
        std::string errorText = std::string("Unable to create SDL Window: ") + SDL_GetError();
		throw std::runtime_error(errorText);
	}

	if((renderer = SDL_CreateRenderer(window, nullptr)) == NULL) {
        std::string errorText = std::string("Unable to create renderer") + SDL_GetError();
        throw std::runtime_error(errorText);
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
}

void SimpleCanvas::OnEvent(SDL_Event* event) {
}

void SimpleCanvas::Loop(std::function<void(SimpleCanvas*)> userfunction) {
    userfunction(this);
}

void SimpleCanvas::Render()
{
    SDL_RenderClear(renderer);

	void* texturePixelData;
	int texturePitch;
	SDL_LockTexture(sdlTexture, nullptr, &texturePixelData, &texturePitch);
	SDL_memcpy(texturePixelData, screenPixels.data(), WINDOW_HEIGHT * texturePitch);
	SDL_UnlockTexture(sdlTexture);

	SDL_RenderTexture(renderer, sdlTexture, NULL, NULL);

	SDL_RenderPresent(renderer);

	SDL_DestroyTexture(sdlTexture);
}

void SimpleCanvas::Run(std::function<void(SimpleCanvas*)> userfunction)
{
    SDL_Event event;

	while(running) {
		while(SDL_PollEvent(&event)) {
			OnEvent(&event);

			if(event.type == SDL_EVENT_QUIT) {
				running = false;
			} else if (eventHandler.has_value()) {
				(*eventHandler)(event);
			}
		}

		Loop(userfunction);
		Render();

		SDL_Delay(1); // Breath
	}
}

std::vector<int>& SimpleCanvas::GetPixelStore()
{
    return screenPixels;
}
