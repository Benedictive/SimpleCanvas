#include "simplecanvas/simple_canvas.hpp"

#include <stdexcept>
#include <iostream>

SimpleCanvas::SimpleCanvas(unsigned int winHeight, unsigned int winWidth)
    : WINDOW_HEIGHT(winHeight), WINDOW_WIDTH(winWidth), screenPixels(WINDOW_HEIGHT * WINDOW_WIDTH)
{
    InitSDL();
    sdlDrawingSurface = SDL_CreateRGBSurface(0,WINDOW_WIDTH,WINDOW_HEIGHT,32,0xFF000000,0x00FF0000,0x0000FF00,0);
	SDL_SetSurfaceBlendMode(sdlDrawingSurface, SDL_BLENDMODE_NONE);
}

SimpleCanvas::~SimpleCanvas()
{
    if (sdlDrawingSurface) {
        SDL_FreeSurface(sdlDrawingSurface);
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
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::string errorText = std::string("Unable to Init SDL: ") + SDL_GetError();
        throw std::runtime_error(errorText);
	}

	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Unable to Init hinting: " << SDL_GetError() << std::endl;
	}

	if((window = SDL_CreateWindow(
		"Simplescreendrawer",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)
	) == NULL) {
        std::string errorText = std::string("Unable to create SDL Window: ") + SDL_GetError();
		throw std::runtime_error(errorText);
	}

	if((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
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

	int surfacePitch = sdlDrawingSurface->pitch;
	SDL_memcpy(sdlDrawingSurface->pixels, screenPixels.data(), WINDOW_HEIGHT * surfacePitch);

	SDL_Texture* sdlTexture;
	sdlTexture = SDL_CreateTextureFromSurface(renderer, sdlDrawingSurface);

	int width, height;
	SDL_QueryTexture(sdlTexture, NULL, NULL, &width, &height);
	SDL_Rect destination = {0, 0, width, height};

	SDL_RenderCopy(renderer, sdlTexture, NULL, &destination);

	SDL_RenderPresent(renderer);

	SDL_DestroyTexture(sdlTexture);
}

void SimpleCanvas::Run(std::function<void(SimpleCanvas*)> userfunction)
{
    SDL_Event event;

	while(running) {
		while(SDL_PollEvent(&event) != 0) {
			OnEvent(&event);

			if(event.type == SDL_QUIT) {
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
