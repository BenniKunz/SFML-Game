#pragma once
#include "IObserver.h"
#include "string"
#include "GameEvent.h"
#include "IMenuPart.h"
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Player.h"

namespace Engine
{
	class Hud
		:public IObserver, public IMenuPart
	{
	public:

		Hud(GameData& data, std::shared_ptr<Player> player);
		virtual ~Hud();

		// Inherited via IObserver
		virtual void OnNotify(GameEvent gameEvent, IGamePart& gamePart) override;
		virtual void Display() override;

		int GetNumberOfEnemiesDestroyed();
	private:
		GameData& _data;
		std::shared_ptr<Player> _player;
		int _numberOfEnemies;
		int _enemiesReachedTarget;
		int _enemiesDestroyed;

		sf::Text _numberOfEnemiesText;
		sf::Text _enemiesReachedTargetText;
		sf::Text _activeAmmoText;
		sf::Text _itemText;
		sf::Clock _clock;
		sf::Time _elapsed;
		sf::Sprite _weaponTexture;
		sf::Sprite _ammoIcon;
		sf::Sprite _hudTable;
		sf::Sprite _hp;
		sf::Sound _enemyDestruction;
		bool _clockStarted{ false };

		bool _itemCollected { false };

		void SetTextAttributes(sf::Text& text, sf::Font&, std::string output, sf::Color color, int characterSize, int x, int y);
		void ChangeWeaponTexture();

		// Inherited via IGamePart
		virtual void InputHandler() override;

		virtual void Update(float dt) override;

		virtual void Draw() override;

		void DrawItemCollectedFeedback();
		void DrawHP();

	};
	
}


