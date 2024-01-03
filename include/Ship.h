#pragma once
#include "Constants.h"
#include "TextureManager.h"
#include "Globals.h"

#include <SDL_mixer.h>

class Ship
{
public:
	Ship();

	void CreateShip();

	void Free();
	void handleEvent(SDL_Event& e);
	void Update();
	void Render();

	void playSound();

	void SetPos(int x, int y);
	void DistractLives();

	int GetLives() const;
	int GetPosX() const;
	int GetPosY() const;
	int GetWidth() const;
	int GetHeight() const;

	SDL_Rect GetRect() const { return m_shipTexture->GetRect(); }
private:
	TextureManager* m_shipTexture{ nullptr };
	Mix_Chunk* m_shootChunk{ nullptr };

	int m_lives{ 1 };

	bool m_isInvinsible{ false };
	Uint32 m_invinsibleTime;
};

