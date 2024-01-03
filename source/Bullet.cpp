#include "Bullet.h"
#include <iostream>

Bullet::Bullet(bool isEnemy) : m_isEnemy{ isEnemy }
{
	if (!isEnemy)
	{
		m_bulletTexture = new TextureManager{ "assets/BulletANDParticles.png" };
	}
	else
	{
		m_bulletTexture = new TextureManager{ "assets/BulletANDParticlesENEMY.png" };
	}
	m_bulletTexture->SetWidth(16);
}

Bullet::~Bullet()
{
	delete m_bulletTexture;
}

void Bullet::Destroy()
{
	isDestroying = true;
}

void Bullet::Update()
{
	if (!m_isEnemy)
	{
		m_bulletTexture->SetPos(GetPosX(), GetPosY() - 5);
	}
	else
	{
		m_bulletTexture->SetPos(GetPosX(), GetPosY() + 5);
	}
	
}

void Bullet::Render()
{
	if (!isDestroying)
	{
		m_bulletTexture->Render(&m_rect[0]);
	}
	else
	{
		m_bulletTexture->Render(&m_rect[frame / 8]);
		++frame;
	}
	
}

void Bullet::setPos(int x, int y)
{
	m_bulletTexture->SetPos(x, y);
}
