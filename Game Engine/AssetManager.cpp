#include "AssetManager.h"

namespace Engine
{

	AssetManager::AssetManager()
	{
	}

	AssetManager::~AssetManager()
	{
	}

	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture texture;

		if (texture.loadFromFile(fileName))
		{
			//this->_textures[name] = texture;
			this->_textures.insert(std::make_pair(name, texture));
			
		}
	}

	sf::Texture& AssetManager::GetTexture(std::string name)
	{
		return this->_textures[name];
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();

		if (font->loadFromFile(fileName))
		{
			this->_fonts[name] = font;
		}

	}

	std::shared_ptr<sf::Font> AssetManager::GetFont(std::string name)
	{
		return this->_fonts[name];
	}
	void AssetManager::LoadSound(std::string name, std::string fileName)
	{
		std::shared_ptr<sf::SoundBuffer> buffer = std::make_shared<sf::SoundBuffer>();

		if (buffer->loadFromFile(fileName))
		{
			this->_sounds.insert(std::make_pair(name, buffer));
		}
	}

	std::shared_ptr<sf::SoundBuffer> AssetManager::GetSound(std::string name)
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

