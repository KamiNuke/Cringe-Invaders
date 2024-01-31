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

	m_lives = 2 + saveFile.GetAdditionalLives();
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

	if (m_invinsibleTime + 2000 < SDL_GetTicks() && m_isInvinsible)
	{
		m_invinsibleTime = 0;
		m_isInvinsible = false;
	}
}

void Ship::Render()
{
	m_shipTexture->Render();
	//SDL_Rect hitbox{ m_shipTexture->GetRect().x + 5, m_shipTexture->GetRect().y + 5, m_shipTexture->GetRect().w - 10, m_shipTexture->GetRect().h - 10};
	//SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0, 0xFF);
	//SDL_RenderDrawRect(renderer, &hitbox);
	if (m_isInvinsible)
	{
		Uint8 alphaFirst{ 0 };
		Uint8 alphaSecond{ 75 };
		if (m_invinsibleTime + 2000 < SDL_GetTicks())
		{
			m_shipTexture->setAlpha(alphaFirst);
		}
		else if (m_invinsibleTime + 1800 < SDL_GetTicks())
		{
			m_shipTexture->setAlpha(alphaSecond);
		}
		else if (m_invinsibleTime + 1600 < SDL_GetTicks())
		{
			m_shipTexture->setAlpha(alphaFirst);
		}
		else if (m_invinsibleTime + 1400 < SDL_GetTicks())
		{
			m_shipTexture->setAlpha(alphaSecond);
		}
		else if (m_invinsibleTime + 1200 < SDL_GetTicks())
		{
			m_shipTexture->setAlpha(alphaFirst);
		}
		else if(m_invinsibleTime + 1000 < SDL_GetTicks())
		{
			m_shipTexture->setAlpha(alphaSecond);
		}
		else if (m_invinsibleTime + 800< SDL_GetTicks())
		{
			m_shipTexture->setAlpha(alphaFirst);
		}
		else if (m_invinsibleTime + 600 < SDL_GetTicks())
		{
			m_shipTexture->setAlpha(alphaSecond);
		}
		else if (m_invinsibleTime + 400 < SDL_GetTicks())
		{
			m_shipTexture->setAlpha(alphaFirst);
		}
		else if (m_invinsibleTime + 200 < SDL_GetTicks())
		{
			m_shipTexture->setAlpha(alphaSecond);
		}
		else if (m_invinsibleTime < SDL_GetTicks())
		{
			m_shipTexture->setAlpha(alphaFirst);
		}
		//else if(m_invinsibleTime + 500 < SDL_GetTicks())
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
		m_invinsibleTime = SDL_GetTicks();
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

SDL_Rect Ship::GetRect()
{
	return SDL_Rect{ m_shipTexture->GetRect().x + 5, m_shipTexture->GetRect().y + 5, m_shipTexture->GetRect().w - 10, m_shipTexture->GetRect().h - 10 };
}
