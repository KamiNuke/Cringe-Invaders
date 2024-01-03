#include "TextureManager.h"
#include "Globals.h"

#include <SDL_image.h>
#include <iostream>

TextureManager::TextureManager(std::string path)
{
	if (!CreateTextureFromSurface(path))
	{
		std::cerr << "Texture hasn't been created" << '\n';
	}
}

TextureManager::~TextureManager()
{
	Free();
}

void TextureManager::Free()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_rect.w = 0;
		m_rect.h = 0;
	}
}

bool TextureManager::CreateTextureFromSurface(std::string path)
{
	SDL_Surface* tempSurface{ IMG_Load(path.c_str()) };
	if (tempSurface == nullptr)
	{
		std::cerr << "tempSurface couldn't load image from IMG_Load(): " << IMG_GetError() << '\n';
		return false;
	}
	//SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0xFF, 0xFF));
	m_rect.w = tempSurface->w;
	m_rect.h = tempSurface->h;

	SDL_Texture* tempTexture{ SDL_CreateTextureFromSurface(renderer, tempSurface) };
	if (tempSurface == nullptr)
	{
		std::cerr << "tempTexture couldn't be created from SDL_CreateTextureFromSurface(): " << SDL_GetError() << '\n';
		return false;
	}
	m_texture = tempTexture;

	SDL_FreeSurface(tempSurface);

	return true;
}

void TextureManager::Render(SDL_Rect* rect)
{
	//SDL_RenderCopyEx(renderer, m_texture, nullptr, nullptr, 0, nullptr, SDL_FLIP_NONE);
	if (rect != nullptr)
	{
		SDL_RenderCopy(renderer, m_texture, rect, &m_rect);
	}
	else
	{
		SDL_RenderCopy(renderer, m_texture, NULL, &m_rect);
	}
}