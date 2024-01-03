#pragma once
#include "SDL.h"

class Window
{
public:
	Window();
	~Window();

	void Init();
	void Free();

	SDL_Window* getWindow() const { return m_window; }
private:
	SDL_Window* m_window{ nullptr };
};

