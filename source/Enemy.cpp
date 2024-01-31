#include "Enemy.h"

#include <iostream>

Enemy::Enemy()
{
}

void Enemy::CreateShip()
{
	m_shipTexture = new TextureManager{ "assets/ships/defaultEnemy.png" };

	m_shootChunk = Mix_LoadWAV("assets/sounds/laserShoot.wav");
	if (m_shootChunk == nullptr)
	{
		std::cerr << "m_shootChunk is nullptr: " << Mix_GetError() << '\n';
	}
}

void Enemy::Free()
{
	delete m_shipTexture;
	Mix_FreeChunk(m_shootChunk);
	m_shootChunk = nullptr;
}

void Enemy::Update()
{
	SetPos(GetPosX(), GetPosY() + 1);
}

void Enemy::Render()
{
	m_shipTexture->Render();
}

void Enemy::SetPos(int x, int y)
{
	m_shipTexture->SetPos(x, y);
}

int Enemy::GetPosX() const
{
	return m_shipTexture->GetPosX();
}

void Enemy::playSound()
{
	Mix_PlayChannel(-1, m_shootChunk, 0);
}

int Enemy::GetPosY() const
{
	return m_shipTexture->GetPosY();
}

SDL_Rect Enemy::GetRect()
{
	return SDL_Rect{ m_shipTexture->GetRect().x + 5,m_shipTexture->GetRect().y + 5, m_shipTexture->GetRect().w - 10, m_shipTexture->GetRect().h - 10 };
}