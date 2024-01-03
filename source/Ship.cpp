#include "Ship.h"

#include <iostream>

Ship::Ship()
{
}

void Ship::CreateShip()
{
	m_shootChunk = Mix_LoadWAV("assets/sounds/shoot.wav");
	if (m_shootChunk == nullptr)
	{
		std::cerr << "m_shootChunk is nullptr: " << Mix_GetError() << '\n';
	}

	m_shipTexture = new TextureManager{ "assets/ships/mainShip.png" };

	m_lives = 1 + saveFile.GetAdditionalLives();
	m_isInvinsible = false;
}

void Ship::Free()
{
	delete m_shipTexture;
	Mix_FreeChunk(m_shootChunk);
	m_shootChunk = nullptr;
}

void Ship::handleEvent(SDL_Event& e)
{

}

void Ship::Update()
{
	const Uint8* keyState{ SDL_GetKeyboardState(0) };
	if (keyState[SDL_SCANCODE_LEFT])
	{
		SetPos(GetPosX() - 3, GetPosY());
	}
	if (keyState[SDL_SCANCODE_RIGHT])
	{
		SetPos(GetPosX() + 3, GetPosY());
	}

	if (GetPosX() > constants::SCREEN_WIDTH - m_shipTexture->GetWidth())
	{
		SetPos(constants::SCREEN_WIDTH - m_shipTexture->GetWidth(), GetPosY());
	}
	else if (GetPosX() < 0)
	{
		SetPos(0, GetPosY());
	}

	if (m_invinsibleTime < SDL_GetTicks() && m_isInvinsible)
	{
		m_invinsibleTime = 0;
		m_isInvinsible = false;
	}
}

void Ship::Render()
{
	m_shipTexture->Render();
	if (m_isInvinsible)
	{
		m_shipTexture->setAlpha(100);
	}
	else
	{
		m_shipTexture->setAlpha(255);
	}
}

void Ship::playSound()
{
	Mix_PlayChannel(-1, m_shootChunk, 0);
}

void Ship::SetPos(int x, int y)
{
	m_shipTexture->SetPos(x, y);
}

void Ship::DistractLives()
{
	if (!m_isInvinsible)
	{
		m_lives -= 1;
		m_isInvinsible = true;
		m_invinsibleTime = SDL_GetTicks() + 1500;
	}
}

int Ship::GetLives() const
{
	return m_lives;
}

int Ship::GetPosX() const
{ 
	return m_shipTexture->GetPosX();
}

int Ship::GetPosY() const
{ 
	return m_shipTexture->GetPosY();
}

int Ship::GetWidth() const
{ 
	return m_shipTexture->GetWidth(); 
}

int Ship::GetHeight() const
{
	return m_shipTexture->GetHeight();
}
