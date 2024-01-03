#pragma once
#include <SDL.h>	
#include <SDL_ttf.h>
#include <string>

class Font
{
public:
	Font();
	~Font();

	void CreateFont(std::string text = "", SDL_Color color = SDL_Color{});
	void ChangeColor(SDL_Color color);
	
	void Free();
	void Render();

	void SetPos(int x, int y);
	int GetWidth() const { return m_rect.w; }
	int GetHeight() const { return m_rect.h; }
private:
	SDL_Texture* CreateTextureForFont(SDL_Color color);

private:
	TTF_Font* m_font{ nullptr };
	SDL_Texture* m_fontTexture{ nullptr };

	SDL_Rect m_rect{};
	std::string m_text{};
};

