#pragma once
#include "SDL.h"
#include <string>
#include "Font.h"

class TextureManager
{
public:
	TextureManager(std::string path);
	~TextureManager();

	void Free();
	bool CreateTextureFromSurface(std::string path);
	void Render(SDL_Rect* rect = nullptr);

	void setAlpha(Uint8 alpha) { SDL_SetTextureAlphaMod(m_texture, alpha); }
	void SetColorMod(Uint8 r, Uint8 g, Uint8 b) { SDL_SetTextureColorMod(m_texture, r, g, b); }

	void SetPos(int x, int y) { m_rect.x = x; m_rect.y = y; }
	int GetPosX() const { return m_rect.x; }
	int GetPosY() const { return m_rect.y; }
	SDL_Texture* GetTexture() const { return m_texture; }
	int GetWidth() const { return m_rect.w; }
	int GetHeight() const { return m_rect.h; }

	void SetWidth(int w) { m_rect.w = w; }
	void SetHeight(int h) { m_rect.h = h; }

	SDL_Rect GetRect() { return m_rect; }
private:
	SDL_Texture* m_texture{ nullptr };

	SDL_Rect m_rect;
};

