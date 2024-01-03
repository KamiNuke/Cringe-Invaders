#include "Window.h"
#include "Constants.h"
#include "Globals.h"

#include <SDL_image.h>

Window::Window()
{
	Init();
}

Window::~Window()
{
	Free();
}

void Window::Init()
{
	m_window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		constants::SCREEN_WIDTH, constants::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	SDL_Surface* tempSurface{ IMG_Load("assets/icon.png") };
	SDL_SetWindowIcon(m_window, tempSurface);
	SDL_FreeSurface(tempSurface);

	renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
}

void Window::Free()
{
	SDL_DestroyWindow(m_window);
	m_window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
}
