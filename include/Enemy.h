#pragma once
#include "TextureManager.h"

#include <SDL_mixer.h>

class Enemy
{
public:
	Enemy();

	void CreateShip();

	void Free();
	void Update();
	void Render();

	void playSound();

	void SetPos(int x, int y);
	int GetPosX() const;
	int GetPosY() const;

	SDL_Rect GetRect() { return m_shipTexture->GetRect(); }
private:
	TextureManager* m_shipTexture{ nullptr };

	Mix_Chunk* m_shootChunk{ nullptr };
};