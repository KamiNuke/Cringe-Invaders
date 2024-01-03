#include "GameState.h"
#include "MenuState.h"
#include "Globals.h"
#include "Constants.h"
#include <iostream>

std::size_t MAX_ENEMIES{ 20 };

GameState GameState::sGameState;

GameState* GameState::Get()
{
	return &sGameState;
}

void GameState::Enter()
{
	m_background = new TextureManager{ "assets/backgrounds/background1.png" };

	m_scoreText = new Font{};
	m_scoreText->CreateFont("Score");
	m_scoreText->SetPos(0 ,constants::SCREEN_HEIGHT - m_scoreText->GetHeight());

	m_livesText = new Font{};
	m_livesText->CreateFont("Lives: " + std::to_string(m_ship.GetLives()));
	m_livesText->SetPos(constants::SCREEN_WIDTH - m_scoreText->GetWidth() - 25, constants::SCREEN_HEIGHT - m_scoreText->GetHeight());

	m_TimeSecond = new Font{};
	m_TimeSecond->CreateFont("Seconds: ");
	m_TimeSecond->SetPos(0, 10);

	m_ship.CreateShip();
	m_ship.SetPos((constants::SCREEN_WIDTH / 2) - m_ship.GetWidth(), (constants::SCREEN_HEIGHT - 50) - m_ship.GetHeight());

	m_music = Mix_LoadMUS("assets/sounds/song1.mp3");
	Mix_PlayMusic(m_music, 5);

	m_score = 0;

	startTime = SDL_GetTicks();
}

void GameState::Exit()
{
	int temp = (SDL_GetTicks() - startTime) / 1000;
	if (!(saveFile.GetSurvivedSeconds() > temp))
	{
		saveFile.WriteToFileSurvivedSeconds(temp);
	}

	m_ship.Free();

	for (std::size_t i{ 0 }; i < m_bullets.size(); ++i)
	{
		delete m_bullets[i];
	}
	m_bullets.clear();

	for (std::size_t i{ 0 }; i < m_enemyBullets.size(); ++i)
	{
		delete m_enemyBullets[i];
	}
	m_enemyBullets.clear();

	for (std::size_t i{ 0 }; i < m_enemies.size(); ++i)
	{
		m_enemies[i].Free();
	}
	m_enemies.clear();

	delete m_background;
	m_background = nullptr;

	saveFile.WriteToFileCredits(saveFile.GetCredits() + m_score);
	delete m_scoreText;
	delete m_livesText;
	delete m_TimeSecond;

	Mix_FreeMusic(m_music);
	m_music = nullptr;
}

void GameState::HandleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
	{
		nextState = MenuState::Get();
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_Z)
	{
		if (m_bullets.size() < saveFile.GetMaxBullets())
		{
			m_bullets.emplace_back(new Bullet{});
			m_bullets[m_bullets.size() - 1]->setPos(m_ship.GetPosX(), m_ship.GetPosY() - 10);
			m_ship.playSound();
		}
	}
	m_ship.handleEvent(e);
}

void GameState::Update()
{
	srand(SDL_GetTicks());

	m_ship.Update();

	//Ordinary Bullets checking
	for (std::size_t i{ 0 }; i < m_bullets.size(); ++i)
	{
		m_bullets[i]->Update();

		if (m_bullets[i]->GetPosY() < 0)
		{
			m_bullets[i]->Destroy();
		}

		if (m_bullets[i]->returnFrame() > 8)
		{
			delete m_bullets[i];
			m_bullets.erase(m_bullets.begin() + i);
		}
	}

	//Ordinary enemyBullets checking
	for (std::size_t i{ 0 }; i < m_enemyBullets.size(); ++i)
	{
		m_enemyBullets[i]->Update();


		if (m_enemyBullets[i]->GetPosY() > constants::SCREEN_HEIGHT)
		{
			m_enemyBullets[i]->Destroy();
		}
		else if (CollisionCheck(m_enemyBullets[i]->GetRect(), m_ship.GetRect()))
		{
			m_ship.DistractLives();
			m_enemyBullets[i]->Destroy();
		}

		if (m_enemyBullets[i]->returnFrame() > 7)
		{
			delete m_enemyBullets[i];
			m_enemyBullets.erase(m_enemyBullets.begin() + i);
		}
	}

	//Collision with bullets
	for (std::size_t i{ 0 }; i < m_enemies.size(); ++i)
	{
		for (std::size_t j{ 0 }; j < m_bullets.size(); ++j)
		{
			if (CollisionCheck(m_enemies[i].GetRect(), m_bullets[j]->GetRect()))
			{
				m_bullets[j]->Destroy();
				m_enemies[i].Free();
				m_enemies.erase(m_enemies.begin() + i);

				m_score += 1;
				break;
			}
		}
	}

	for (std::size_t i{ 0 }; i < m_enemies.size(); ++i)
	{
		m_enemies[i].Update();

		if (m_enemies[i].GetPosY() > 720)
		{
			m_enemies[i].Free();
			m_enemies.erase(m_enemies.begin() + i);
		}
		else if (CollisionCheck(m_ship.GetRect(), m_enemies[i].GetRect()))
		{
			m_enemies[i].Free();
			m_enemies.erase(m_enemies.begin() + i);
			m_ship.DistractLives();
		}
		else if (rand() % 128 > 125)
		{
			m_enemyBullets.emplace_back(new Bullet{ true });
			m_enemyBullets[m_enemyBullets.size() - 1]->setPos(m_enemies[i].GetPosX(), m_enemies[i].GetPosY() + 10);
			m_enemies[i].playSound();
		}
	}

	if (rand() % 64 >= 62)
	{
		if (m_enemies.size() < MAX_ENEMIES)
		{
			m_enemies.emplace_back(Enemy{});
			m_enemies[m_enemies.size() - 1].CreateShip();
			m_enemies[m_enemies.size() - 1].SetPos(rand() % (480 - m_enemies[m_enemies.size() - 1].GetRect().w), 0);
		}
	}

	if (m_ship.GetLives() <= 0)
	{
		nextState = MenuState::Get();
	}


	if (startTime + 120000 < SDL_GetTicks())
	{
		MAX_ENEMIES = 100;
	}
	else if (startTime + 40000 < SDL_GetTicks())
	{
		MAX_ENEMIES = 40;
	}

	m_scoreText->CreateFont("Score: " + std::to_string(m_score));
	m_livesText->CreateFont("Lives: " + std::to_string(m_ship.GetLives()));
	m_TimeSecond->CreateFont("Seconds: " + std::to_string((SDL_GetTicks() - startTime) / 1000) + "s");
}

void GameState::Render()
{
	m_background->Render();
	m_ship.Render();

	for (std::size_t i{ 0 }; i < m_bullets.size(); ++i)
	{
		m_bullets[i]->Render();
	}

	for (std::size_t i{ 0 }; i < m_enemies.size(); ++i)
	{
		m_enemies[i].Render();
	}

	for (std::size_t i{ 0 }; i < m_enemyBullets.size(); ++i)
	{
		m_enemyBullets[i]->Render();
	}

	m_scoreText->Render();
	m_livesText->Render();
	m_TimeSecond->Render();
}