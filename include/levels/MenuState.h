#pragma once
#include "IGameState.h"
#include "TextureManager.h"
#include "Font.h"

#include <SDL_mixer.h>

enum class Button
{
	Play,
	Shop,
	Settings,
	Exit,

	MAX_BUTTONS
};

void operator++(Button& but);
void operator--(Button& but);

class MenuState : public IGameState
{
public:
	static MenuState* Get();
	void Enter();
	void Exit();

	void HandleEvent(SDL_Event& e);
	void Update();
	void Render();


private:
	static MenuState sMenuState;
	MenuState() {};

	TextureManager* m_background{ nullptr };
	Font* m_text1{ nullptr };
	Font* m_text2{ nullptr };
	Font* m_text3{ nullptr };
	Font* m_text4{ nullptr };

	Font* m_controlText{ nullptr };
	Font* m_showHitboxes{ nullptr };
	Font* m_MaxSurvived{ nullptr };

	Mix_Music* m_music{ nullptr };
	Mix_Chunk* m_buttonSound{ nullptr };

	Button m_currentButton{ Button::Play };
};

