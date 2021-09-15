#include "AssetManager.h"
#include <iostream>

namespace Engine
{

	AssetManager::AssetManager()
	{
	}

	AssetManager::~AssetManager()
	{
		std::cout << "AssetManager Destructor" << std::endl;
	}

	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture texture;

		if (texture.loadFromFile(fileName))
		{
			
			this->_textures.insert(std::make_pair(name, texture));
			
		}
	}

	sf::Texture& AssetManager::GetTexture(std::string name)
	{
		return this->_textures[name];
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		sf::Font font;

		if (font.loadFromFile(fileName))
		{
			this->_fonts[name] = font;
		}

	}

	sf::Font& AssetManager::GetFont(std::string name)
	{
		return this->_fonts[name];
	}
	void AssetManager::LoadSound(std::string name, std::string fileName)
	{
		sf::SoundBuffer buffer;

		if (buffer.loadFromFile(fileName))
		{
			this->_sounds.insert(std::make_pair(name, buffer));
		}
	}

	sf::SoundBuffer& AssetManager::GetSound(std::string name)
	{
		return this->_sounds[name];
	}
	void AssetManager::PlayMusic(sf::Music& music, std::string filename, bool isLoop)
	{
		if (music.openFromFile(filename))
		{
			music.play();
			music.setLoop(isLoop);
		}
		else
		{
			//exception handling
		}
	}
}

