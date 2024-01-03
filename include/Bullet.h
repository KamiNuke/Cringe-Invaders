#pragma once
#include "TextureManager.h"
#include "Globals.h"

class Bullet
{
public:
	Bullet(bool isEnemy = false);
	~Bullet();

	void Destroy();
	void Update();
	void Render();

	void setPos(int x, int y);
	int GetPosX() const { return m_bulletTexture->GetPosX(); }
	int GetPosY() const { return m_bulletTexture->GetPosY(); }
	SDL_Rect GetRect() { return m_bulletTexture->GetRect(); }

	int returnFrame() const { return frame / 8 ; }
private:
	TextureManager* m_bulletTexture{ nullptr };

	SDL_Rect m_rect[8]{
		SDL_Rect{0,0,16,16},SDL_Rect{16,0,16,16},SDL_Rect{16 * 2,0,16,16},
		SDL_Rect{16 * 3,0,16,16},SDL_Rect{16 * 4,0,16,16},SDL_Rect{16 * 5,0,16,16},
		SDL_Rect{16 * 6,0,16,16},SDL_Rect{16 * 7,0,16,16}
	};

	bool isDestroying{ false };
	bool m_isEnemy{ false };
	int frame{ 0 };
};

