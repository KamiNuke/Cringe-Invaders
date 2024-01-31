#pragma once
#include "IGameState.h"
#include "TextureManager.h"
#include "Ship.h"
#include "Enemy.h"
#include "Bullet.h"

#include <vector>
#include <SDL_mixer.h>

class GameState : public IGameState
{
public:
	static GameState* Get();
	void Enter();
	void Exit();

	void HandleEvent(SDL_Event& e);
	void Update();
	void Render();
	
private:
	static GameState sGameState;
	~GameState() {};

	TextureManager* m_background{ nullptr };
	Font* m_scoreText{ nullptr };
	int m_score{ 0 };
	Font* m_livesText{ nullptr };
	Font* m_TimeSecond{ nullptr };

	Mix_Music* m_music{ nullptr };
	//Mix_Chunk* damageEffect{ nullptr };

	Uint32 startTime;
	Uint32 shootDelay{ 0 };
	//Uint32 survivedSeconds{ 0 };

	int chanceToSpawn{ 62 };

	std::size_t MAX_ENEMIES{ 20 };
private:
	Ship m_ship;
	std::vector<Bullet*> m_bullets;

	std::vector<Enemy> m_enemies;
	std::vector<Bullet*> m_enemyBullets;
	
	std::size_t activeBullets{ 0 };
};

