#pragma once
#include "IGameState.h"
#include "TextureManager.h"

#include <SDL_mixer.h>

enum class Volume
{
	Zero,
	TwentyFive,
	Fifty,
	SeventyFive,
	OneHundred,

	MAX_BUTTONS
};

void operator++(Volume& vol);
void operator--(Volume& vol);

class SettingsState : public IGameState
{
public:
	static SettingsState* Get();

	void Enter();
	void Exit();

	void HandleEvent(SDL_Event& e);
	void Update();
	void Render();
private:
	static SettingsState sSettingsState;
	SettingsState() {};

private:
	TextureManager* m_background{ nullptr };
	TextureManager* m_button0{ nullptr };
	TextureManager* m_button1{ nullptr };
	TextureManager* m_button2{ nullptr };
	TextureManager* m_button3{ nullptr };
	TextureManager* m_button4{ nullptr };

	Font* m_volumeText{ nullptr };

	Font* m_confirmText{ nullptr };

	Volume m_choosenVolume{ Volume::OneHundred };

	Mix_Chunk* m_swapButtonSound{ nullptr };
	Mix_Chunk* m_confirmSound{ nullptr };
};

