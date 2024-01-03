#include "MainClass.h"
#include "Window.h"
#include "Globals.h"

#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


#include "ExitState.h"
#include "MenuState.h"

MainClass::MainClass()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		std::cerr << "SDL can't be initialed: " << SDL_GetError() << '\n';
	}
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cerr << "IMG can't be initialed: " << IMG_GetError() << '\n';
	}
	if (TTF_Init() != 0)
	{
		std::cerr << "TTF can't be initialed: " << TTF_GetError() << '\n';
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 
	{
		std::cerr << "Mixer can't be initialed: " << Mix_GetError() << '\n';
	}
}

MainClass::~MainClass()
{
	delete state;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void MainClass::Loop()
{
	Mix_Volume(-1, saveFile.GetAudioVolume());
	Mix_VolumeMusic(saveFile.GetAudioVolume());
	state = new MachineState{};

	SDL_Event e;
	while (state->isRunning())
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				state->setNextState(ExitState::Get());
			}
			state->HandleEvent(e);
			
		}
		Update();
		state->changeState();


		Render();
	}
	
}

void MainClass::Update()
{
	state->Update();
}

void MainClass::Render()
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	state->GetState()->Render();

	SDL_RenderPresent(renderer);
}
