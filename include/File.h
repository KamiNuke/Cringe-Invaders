#pragma once
#include <fstream>
#include <SDL_mixer.h>

class File
{
public:
	~File();
	int GetCredits();
	int GetAudioVolume();
	int GetMaxBullets();
	int GetAdditionalLives();
	int GetSurvivedSeconds();

	File(std::string filename);
	void WriteToFileCredits(int credits);
	void WriteToFileAudio(int audioVolume);
	void WriteToFileMaxBullets(int maxBullets);
	void WriteToFileAdditionalLives(int lives);
	void WriteToFileSurvivedSeconds(int seconds);
private:	
	int m_credits{ 0 };
	int m_maxBullets{ 1 };
	int m_audioVolume{ MIX_MAX_VOLUME };
	int m_additionalLives{ 0 };
	Uint32 m_maxSurvived{ 0 };
	std::string m_filename;
};

