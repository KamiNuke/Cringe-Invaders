#include "Font.h"
#include "Globals.h"

#include <iostream>
#include <SDL_image.h>
#include <iostream>

Font::Font()
{
}

Font::~Font()
{
	Free();
	if (m_font != nullptr)
	{
		TTF_CloseFont(m_font);
		m_font = nullptr;
	}
}

void Font::CreateFont(std::string text, SDL_Color color)
{
	Free();
	if (m_font == nullptr)
	{
		m_font = TTF_OpenFont("assets/fonts/Minecraft.ttf", 24);
	}
	m_text = text;
	m_fontTexture = CreateTextureForFont(color);
}

void Font::ChangeColor(SDL_Color color)
{
	Free();
	m_fontTexture = CreateTextureForFont(color);
}

SDL_Texture* Font::CreateTextureForFont(SDL_Color color)
{
	SDL_Surface* tempSurface{ TTF_RenderText_Solid(m_font, m_text.c_str(), color) };
	if (tempSurface == nullptr)
	{
		std::cerr << "tempSurface couldn't load image from IMG_Load(): " << IMG_GetError() << '\n';
		return nullptr;
	}
	m_rect.w = tempSurface->w;
	m_rect.h = tempSurface->h;

	SDL_Texture* tempTexture{ SDL_CreateTextureFromSurface(renderer, tempSurface) };
	if (tempTexture == nullptr)
	{
		std::cerr << "tempTexture couldn't be created from SDL_CreateTextureFromSurface(): " << SDL_GetError() << '\n';
		return nullptr;
	}
	
	SDL_FreeSurface(tempSurface);
	return tempTexture;
}

void Font::Free()
{
	if (m_fontTexture != nullptr)
	{
		SDL_DestroyTexture(m_fontTexture);
		m_fontTexture = nullptr;
	}
}

void Font::Render()
{
	SDL_RenderCopy(renderer, m_fontTexture, NULL, &m_rect);
}

void Font::SetPos(int x, int y)
{
	m_rect.x = x;
	m_rect.y = y;
}