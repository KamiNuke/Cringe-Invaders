#include "MenuState.h"
#include "ExitState.h"
#include "SettingsState.h"
#include "ShopState.h"

#include "Globals.h"
#include "GameState.h"
#include "Constants.h"
#include <iostream>

MenuState MenuState::sMenuState;

MenuState* MenuState::Get()
{
	return &sMenuState;
}

void MenuState::Enter()
{
	m_background = new TextureManager{ "assets/backgrounds/background1.png" };

	m_text1 = new Font{};
	m_text1->CreateFont("Play");
	m_text1->SetPos((constants::SCREEN_WIDTH / 2) - m_text1->GetWidth() + 30, constants::SCREEN_HEIGHT - 500);

	m_text2 = new Font{};
	m_text2->CreateFont("Shop");
	m_text2->SetPos((constants::SCREEN_WIDTH / 2) - m_text2->GetWidth() + 35, constants::SCREEN_HEIGHT - 400);

	m_text3 = new Font{};
	m_text3->CreateFont("Settings");
	m_text3->SetPos((constants::SCREEN_WIDTH / 2) - m_text3->GetWidth() + 57, constants::SCREEN_HEIGHT - 300);

	m_text4 = new Font{};
	m_text4->CreateFont("Exit");
	m_text4->SetPos((constants::SCREEN_WIDTH / 2) - m_text4->GetWidth() + 30, constants::SCREEN_HEIGHT - 200);

	m_MaxSurvived = new Font{};
	m_MaxSurvived->CreateFont("Max seconds: " + std::to_string(saveFile.GetSurvivedSeconds()));
	m_MaxSurvived->SetPos(10, 10);

	m_buttonSound = Mix_LoadWAV("assets/sounds/blipSelect.wav");

	if (m_currentState != SettingsState::Get())
	{
		if (m_currentState != ShopState::Get())
		{
			m_music = Mix_LoadMUS("assets/sounds/menuSong1.mp3");
			Mix_PlayMusic(m_music, 5);
		}
	}
}

void MenuState::Exit()
{
	delete m_background;

	delete m_text1;
	m_text1 = nullptr;

	delete m_text2;
	m_text2 = nullptr;

	delete m_text3;
	m_text3 = nullptr;

	delete m_text4;
	m_text4 = nullptr;

	delete m_MaxSurvived;
	m_MaxSurvived = nullptr;

	if (nextState != SettingsState::Get())
	{
		if (nextState != ShopState::Get())
		{
			Mix_FreeMusic(m_music);
			m_music = nullptr;
		}
	}
	Mix_FreeChunk(m_buttonSound);
	m_buttonSound = nullptr;
}

void MenuState::HandleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_Z)
	{
		switch (m_currentButton)
		{
		case Button::Play:
			nextState = GameState::Get();
			break;
		case Button::Shop:
			nextState = ShopState::Get();
			break;
		case Button::Settings:
			nextState = SettingsState::Get();
			break;
		case Button::Exit:
			nextState = ExitState::Get();
			break;
		default:
			break;
		}
	}
	if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_UP || e.key.keysym.scancode == SDL_SCANCODE_W && e.key.repeat == 0)
	{
		++m_currentButton;
		Mix_PlayChannel(-1, m_buttonSound, 0);
	}
	else if(e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_DOWN || e.key.keysym.scancode == SDL_SCANCODE_S && e.key.repeat == 0)
	{
		--m_currentButton;
		Mix_PlayChannel(-1, m_buttonSound, 0);
	}
}

void MenuState::Update()
{
	switch (m_currentButton)
	{
	case Button::Play:
		m_text1->ChangeColor(SDL_Color{ 210, 0, 0 });
		m_text2->ChangeColor(SDL_Color{ 0, 0, 0 });
		m_text3->ChangeColor(SDL_Color{ 0, 0, 0 });
		m_text4->ChangeColor(SDL_Color{ 0, 0, 0 });
		break;
	case Button::Shop:
		m_text1->ChangeColor(SDL_Color{ 0, 0, 0 });
		m_text2->ChangeColor(SDL_Color{ 210, 0, 0 });
		m_text3->ChangeColor(SDL_Color{ 0, 0, 0 });
		m_text4->ChangeColor(SDL_Color{ 0, 0, 0 });
		break;
	case Button::Settings:
		m_text1->ChangeColor(SDL_Color{ 0, 0, 0 });
		m_text2->ChangeColor(SDL_Color{ 0, 0, 0 });
		m_text3->ChangeColor(SDL_Color{ 210, 0, 0 });
		m_text4->ChangeColor(SDL_Color{ 0, 0, 0 });
		break;
	case Button::Exit:
		m_text1->ChangeColor(SDL_Color{ 0, 0, 0 });
		m_text2->ChangeColor(SDL_Color{ 0, 0, 0 });
		m_text3->ChangeColor(SDL_Color{ 0, 0, 0 });
		m_text4->ChangeColor(SDL_Color{ 210, 0, 0 });
		break;
	default:
		m_text1->ChangeColor(SDL_Color{ 0, 0, 0 });
		m_text2->ChangeColor(SDL_Color{ 0, 0, 0 });
		m_text3->ChangeColor(SDL_Color{ 0, 0, 0 });
		m_text4->ChangeColor(SDL_Color{ 0, 0, 0 });
		break;
	}
}

void MenuState::Render()
{
	m_background->Render();

	m_text1->Render();
	m_text2->Render();
	m_text3->Render();
	m_text4->Render();

	m_MaxSurvived->Render();
}

void operator++(Button& but)
{
	switch (but)
	{
	case Button::Play:
		but = Button::Exit;
		break;
	case Button::Shop:
		but = Button::Play;
		break;
	case Button::Settings:
		but = Button::Shop;
		break;
	case Button::Exit:
		but = Button::Settings;
		break;
	default:
		break;
	}
}

void operator--(Button& but)
{
	switch (but)
	{
	case Button::Play:
		but = Button::Shop;
		break;
	case Button::Shop:
		but = Button::Settings;
		break;
	case Button::Settings:
		but = Button::Exit;
		break;
	case Button::Exit:
		but = Button::Play;
		break;
	default:
		break;
	}
}
