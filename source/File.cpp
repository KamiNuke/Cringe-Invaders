#include "File.h"
#include <iostream>

File::File(std::string filename) : m_filename{ filename }
{
	std::ifstream textOfFile{ m_filename, std::ios::binary | std::ios::in };
	if (!textOfFile.is_open())
	{
		std::cerr << "no such file exist\n";
	}
	else
	{
		textOfFile.read(reinterpret_cast<char*>(&m_credits), sizeof(int));
		textOfFile.read(reinterpret_cast<char*>(&m_audioVolume), sizeof(int));
		textOfFile.read(reinterpret_cast<char*>(&m_maxBullets), sizeof(int));
		textOfFile.read(reinterpret_cast<char*>(&m_additionalLives), sizeof(int));
		textOfFile.read(reinterpret_cast<char*>(&m_maxSurvived), sizeof(Uint32));
	}

	textOfFile.close();
}

void File::WriteToFileAudio(int audioVolume)
{
	m_audioVolume = audioVolume;
}

void File::WriteToFileMaxBullets(int maxBullets)
{
	m_maxBullets = maxBullets;
}

void File::WriteToFileAdditionalLives(int lives)
{
	m_additionalLives = lives;
}

void File::WriteToFileSurvivedSeconds(int seconds)
{
	m_maxSurvived = seconds;
}

void File::WriteToFileCredits(int credits)
{
	m_credits = credits;
}

File::~File()
{
	std::ofstream inputText{ m_filename, std::ios::out | std::ios::binary };
	inputText.write(reinterpret_cast<char*>(&m_credits), sizeof(int));
	inputText.write(reinterpret_cast<char*>(&m_audioVolume), sizeof(int));
	inputText.write(reinterpret_cast<char*>(&m_maxBullets), sizeof(int));
	inputText.write(reinterpret_cast<char*>(&m_additionalLives), sizeof(int));
	inputText.write(reinterpret_cast<char*>(&m_maxSurvived), sizeof(Uint32));
	inputText.close();
}

int File::GetCredits()
{
	return m_credits;
}

int File::GetAudioVolume()
{
	return m_audioVolume;
}

int File::GetMaxBullets()
{
	return m_maxBullets;
}

int File::GetAdditionalLives()
{
	return m_additionalLives;
}

int File::GetSurvivedSeconds()
{
	return m_maxSurvived;
}
