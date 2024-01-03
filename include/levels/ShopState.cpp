#include "ShopState.h"
#include "MenuState.h"

#include "Globals.h"
#include "Constants.h"
#include <iostream>

ShopState ShopState::sShopState;

ShopState* ShopState::Get()
{
	return &sShopState;
}

void ShopState::Enter()
{
	m_background = new TextureManager{ "assets/backgrounds/background1.png" };

	m_shopItem1 = new TextureManager{ "assets/shopItem.png" };
	m_shopItem1->SetPos(85, 20);

	m_shopItem2 = new TextureManager{ "assets/shopItem.png" };
	m_shopItem2->SetPos(85, 220);

	m_shopItem3 = new TextureManager{ "assets/shopItem.png" };
	m_shopItem3->SetPos(85, 420);

	m_coin = new TextureManager{ "assets/coin.png" };
	m_coin->SetPos(0, constants::SCREEN_HEIGHT - 64);

	m_balanceText = new Font{};
	m_balanceText->CreateFont(std::to_string(saveFile.GetCredits()), SDL_Color{ 255, 255, 255 });
	m_balanceText->SetPos(90, constants::SCREEN_HEIGHT - 30);

	m_shopItem1Text = new Font{};
	m_shopItem1Text->CreateFont("+1 SHOOT - 150g", SDL_Color{255, 255, 255});
	m_shopItem1Text->SetPos(m_shopItem1->GetPosX() + 50, m_shopItem1->GetPosY() + 70);

	m_shopItem2Text = new Font{};
	m_shopItem2Text->CreateFont("+1 LIVE - 150g", SDL_Color{ 255, 255, 255 });
	m_shopItem2Text->SetPos(m_shopItem2->GetPosX() + 50, m_shopItem2->GetPosY() + 70);

	m_shopItem3Text = new Font{};
	m_shopItem3Text->CreateFont("DELETE SAVE - 50g", SDL_Color{ 255, 255, 255 });
	m_shopItem3Text->SetPos(m_shopItem3->GetPosX() + 30, m_shopItem3->GetPosY() + 70);

	m_switchSound = Mix_LoadWAV("assets/sounds/blipSelect.wav");
	m_confirmSound = Mix_LoadWAV("assets/sounds/Confirm.wav");
}

void ShopState::Exit()
{
	delete m_background;
	m_background = nullptr;

	delete m_shopItem1;
	m_shopItem1 = nullptr;

	delete m_shopItem2;
	m_shopItem2 = nullptr;

	delete m_shopItem3;
	m_shopItem3 = nullptr;

	delete m_coin;
	m_coin = nullptr;

	delete m_balanceText;
	m_balanceText = nullptr;

	delete m_shopItem1Text;
	m_shopItem1Text = nullptr;

	delete m_shopItem2Text;
	m_shopItem2Text = nullptr;

	delete m_shopItem3Text;
	m_shopItem3Text = nullptr;

	Mix_FreeChunk(m_switchSound);
	m_switchSound = nullptr;

	Mix_FreeChunk(m_confirmSound);
	m_confirmSound = nullptr;
}

void ShopState::HandleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
	{
		nextState = MenuState::Get();
	}

	if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_UP || e.key.keysym.scancode == SDL_SCANCODE_W && e.key.repeat == 0)
	{
		++m_chosenItem;
		Mix_PlayChannel(-1, m_switchSound, 0);
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_DOWN || e.key.keysym.scancode == SDL_SCANCODE_S && e.key.repeat == 0)
	{
		--m_chosenItem;
		Mix_PlayChannel(-1, m_switchSound, 0);
	}

	if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_Z && e.key.repeat == 0)
	{
		Mix_PlayChannel(-1, m_confirmSound, 0);
		switch (m_chosenItem)
		{
		case ShopItem::FirstItem:
			if (saveFile.GetCredits() >= 150)
			{
				saveFile.WriteToFileMaxBullets(saveFile.GetMaxBullets() + 1);
				saveFile.WriteToFileCredits(saveFile.GetCredits() - 100);
			}
			break;
		case ShopItem::SecondItem:
			if (saveFile.GetCredits() >= 150)
			{
				saveFile.WriteToFileAdditionalLives(saveFile.GetAdditionalLives() + 1);
				saveFile.WriteToFileCredits(saveFile.GetCredits() - 150);
			}
			break;
		case ShopItem::ThirdItem:
			if (saveFile.GetCredits() >= 50)
			{
				saveFile.WriteToFileAdditionalLives(0);
				saveFile.WriteToFileCredits(0);
				saveFile.WriteToFileAudio(MIX_MAX_VOLUME);
				saveFile.WriteToFileMaxBullets(1);
				saveFile.WriteToFileSurvivedSeconds(-1);
			}
			break;
		default:
			break;
		}
		
	}
}

void ShopState::Update()
{
	switch (m_chosenItem)
	{
	case ShopItem::FirstItem:
		m_shopItem1->SetColorMod(50, 100, 255);
		m_shopItem2->SetColorMod(255, 255, 255);
		m_shopItem3->SetColorMod(255, 255, 255);
		break;
	case ShopItem::SecondItem:
		m_shopItem1->SetColorMod(255, 255, 255);
		m_shopItem2->SetColorMod(50, 100, 255);
		m_shopItem3->SetColorMod(255, 255, 255);
		break;
	case ShopItem::ThirdItem:
		m_shopItem1->SetColorMod(255, 255, 255);
		m_shopItem2->SetColorMod(255, 255, 255);
		m_shopItem3->SetColorMod(50, 100, 255);
		break;
	default:
		break;
	}

	m_balanceText->CreateFont(std::to_string(saveFile.GetCredits()), SDL_Color{ 255, 255, 255 });
}

void ShopState::Render()
{
	m_background->Render();

	m_shopItem1->Render();
	m_shopItem2->Render();
	m_shopItem3->Render();

	m_shopItem1Text->Render();
	m_shopItem2Text->Render();
	m_shopItem3Text->Render();

	m_coin->Render();
	m_balanceText->Render();	
}

void operator--(ShopItem& shopitem)
{
	switch (shopitem)
	{
	case ShopItem::FirstItem:
		shopitem = ShopItem::SecondItem;
		break;
	case ShopItem::SecondItem:
		shopitem = ShopItem::ThirdItem;
		break;
	case ShopItem::ThirdItem:
		shopitem = ShopItem::FirstItem;
		break;
	default:
		break;
	}
}

void operator++(ShopItem& shopitem)
{
	switch (shopitem)
	{
	case ShopItem::FirstItem:
		shopitem = ShopItem::ThirdItem;
		break;
	case ShopItem::SecondItem:
		shopitem = ShopItem::FirstItem;
		break;
	case ShopItem::ThirdItem:
		shopitem = ShopItem::SecondItem;
		break;
	default:
		break;
	}
}