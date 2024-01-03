#include "SettingsState.h"
#include "Globals.h"
#include "MenuState.h"
#include "Constants.h"

SettingsState SettingsState::sSettingsState;

SettingsState* SettingsState::Get()
{
	return &sSettingsState;
}

void SettingsState::Enter()
{
	m_background = new TextureManager{ "assets/backgrounds/background1.png" };

	m_button0 = new TextureManager{ "assets/button/button0.png" };
	m_button1 = new TextureManager{ "assets/button/button1.png" };
	m_button2 = new TextureManager{ "assets/button/button2.png" };
	m_button3 = new TextureManager{ "assets/button/button3.png" };
	m_button4 = new TextureManager{ "assets/button/button4.png" };

	m_button0->SetPos(16, constants::SCREEN_HEIGHT - 450);
	m_button1->SetPos(64 * 1.7, constants::SCREEN_HEIGHT - 450);
	m_button2->SetPos(64 * 3.3, constants::SCREEN_HEIGHT - 450);
	m_button3->SetPos(64 * 4.8, constants::SCREEN_HEIGHT - 450);
	m_button4->SetPos(64 * 6.3, constants::SCREEN_HEIGHT - 450);

	m_volumeText = new Font{};
	m_volumeText->CreateFont("Music and Sound volume ");
	m_volumeText->SetPos((constants::SCREEN_WIDTH / 2) - m_volumeText->GetWidth() + 186, constants::SCREEN_HEIGHT - 500);

	m_confirmText = new Font{};
	m_confirmText->CreateFont("Press Z to confirm");
	m_confirmText->SetPos((constants::SCREEN_WIDTH / 2) - m_confirmText->GetWidth() + 140, constants::SCREEN_HEIGHT - 100);

	m_swapButtonSound = Mix_LoadWAV("assets/sounds/blipSelectSettings.wav");
	m_confirmSound = Mix_LoadWAV("assets/sounds/Confirm.wav");
}

void SettingsState::Exit()
{
	delete m_background;
	m_background = nullptr;

	delete m_volumeText;
	m_volumeText = nullptr;

	delete m_confirmText;
	m_confirmText = nullptr;

	delete m_button0;
	delete m_button1;
	delete m_button2;
	delete m_button3;
	delete m_button4;

	m_button0 = nullptr;
	m_button1 = nullptr;
	m_button2 = nullptr;
	m_button3 = nullptr;
	m_button4 = nullptr;

	Mix_FreeChunk(m_swapButtonSound);
	Mix_FreeChunk(m_confirmSound);
}

void SettingsState::HandleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
	{
		nextState = MenuState::Get();
	}

	if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_RIGHT || e.key.keysym.scancode == SDL_SCANCODE_D && e.key.repeat == 0)
	{
		++m_choosenVolume;
		Mix_PlayChannel(-1, m_swapButtonSound, 0);
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_LEFT || e.key.keysym.scancode == SDL_SCANCODE_A && e.key.repeat == 0)
	{
		--m_choosenVolume;
		Mix_PlayChannel(-1, m_swapButtonSound, 0);
	}

	if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_Z && e.key.repeat == 0)
	{
		Mix_PlayChannel(-1, m_confirmSound, 0);
		switch (m_choosenVolume)
		{
		case Volume::Zero:
			saveFile.WriteToFileAudio(0);
			Mix_Volume(-1, 0);
			Mix_VolumeMusic(0);
			break;
		case Volume::TwentyFive:
			saveFile.WriteToFileAudio(32);
			Mix_Volume(-1, 32);
			Mix_VolumeMusic(32);
			break;
		case Volume::Fifty:
			saveFile.WriteToFileAudio(64);
			Mix_Volume(-1, 64);
			Mix_VolumeMusic(64);
			break;
		case Volume::SeventyFive:
			saveFile.WriteToFileAudio(92);
			Mix_Volume(-1, 92);
			Mix_VolumeMusic(92);
			break;
		case Volume::OneHundred:
			saveFile.WriteToFileAudio(MIX_MAX_VOLUME);
			Mix_Volume(-1, MIX_MAX_VOLUME);
			Mix_VolumeMusic(MIX_MAX_VOLUME);
			break;
		default:
			break;
		}
		
	}
}

void SettingsState::Update()
{
	switch (m_choosenVolume)
	{
	case Volume::Zero:
		m_button0->SetColorMod(0, 255, 255);
		m_button1->SetColorMod(255, 255, 255);
		m_button2->SetColorMod(255, 255, 255);
		m_button3->SetColorMod(255, 255, 255);
		m_button4->SetColorMod(255, 255, 255);
		break;
	case Volume::TwentyFive:
		m_button0->SetColorMod(255, 255, 255);
		m_button1->SetColorMod(0, 255, 255);
		m_button2->SetColorMod(255, 255, 255);
		m_button3->SetColorMod(255, 255, 255);
		m_button4->SetColorMod(255, 255, 255);
		break;
	case Volume::Fifty:
		m_button0->SetColorMod(255, 255, 255);
		m_button1->SetColorMod(255, 255, 255);
		m_button2->SetColorMod(0, 255, 255);
		m_button3->SetColorMod(255, 255, 255);
		m_button4->SetColorMod(255, 255, 255);
		break;
	case Volume::SeventyFive:
		m_button0->SetColorMod(255, 255, 255);
		m_button1->SetColorMod(255, 255, 255);
		m_button2->SetColorMod(255, 255, 255);
		m_button3->SetColorMod(0, 255, 255);
		m_button4->SetColorMod(255, 255, 255);
		break;
	case Volume::OneHundred:
		m_button0->SetColorMod(255, 255, 255);
		m_button1->SetColorMod(255, 255, 255);
		m_button2->SetColorMod(255, 255, 255);
		m_button3->SetColorMod(255, 255, 255);
		m_button4->SetColorMod(0, 255, 255);
		break;
	default:
		break;
	}
}

void SettingsState::Render()
{
	m_background->Render();
	m_volumeText->Render();
	m_confirmText->Render();
	m_button0->Render();
	m_button1->Render();
	m_button2->Render();
	m_button3->Render();
	m_button4->Render();
}

void operator++(Volume& vol)
{
	switch (vol)
	{
	case Volume::Zero:
		vol = Volume::TwentyFive;
		break;
	case Volume::TwentyFive:
		vol = Volume::Fifty;
		break;
	case Volume::Fifty:
		vol = Volume::SeventyFive;
		break;
	case Volume::SeventyFive:
		vol = Volume::OneHundred;
		break;
	case Volume::OneHundred:
		vol = Volume::Zero;
		break;
	default:
		break;
	}
}

void operator--(Volume& vol)
{
	switch (vol)
	{
	case Volume::Zero:
		vol = Volume::OneHundred;
		break;
	case Volume::TwentyFive:
		vol = Volume::Zero;
		break;
	case Volume::Fifty:
		vol = Volume::TwentyFive;
		break;
	case Volume::SeventyFive:
		vol = Volume::Fifty;
		break;
	case Volume::OneHundred:
		vol = Volume::SeventyFive;
		break;
	default:
		break;
	}
}