#pragma once
#include "IGameState.h"
#include "TextureManager.h"

#include "Font.h"

#include <SDL_mixer.h>

enum class ShopItem
{
	FirstItem,
	SecondItem,
	ThirdItem,

	MAX_ITEMS
};

void operator++(ShopItem& shopitem);
void operator--(ShopItem& shopitem);

class ShopState : public IGameState
{
public:
	static ShopState* Get();
	void Enter();
	void Exit();

	void HandleEvent(SDL_Event& e);
	void Update();
	void Render();

	
private:
	static ShopState sShopState;
	~ShopState() {};
private:
	TextureManager* m_background{ nullptr };

	TextureManager* m_shopItem1{ nullptr };
	TextureManager* m_shopItem2{ nullptr };
	TextureManager* m_shopItem3{ nullptr };
	Font* m_shopItem1Text{ nullptr };
	Font* m_shopItem2Text{ nullptr };
	Font* m_shopItem3Text{ nullptr };

	TextureManager* m_coin{ nullptr };

	Font* m_balanceText{ nullptr };

	ShopItem m_chosenItem{ ShopItem::FirstItem };

	Mix_Chunk* m_switchSound{ nullptr };
	Mix_Chunk* m_confirmSound{ nullptr };
};