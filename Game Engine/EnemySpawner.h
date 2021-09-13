#pragma once
#include "IGamePart.h"
#include "Node.h"
#include "Game.h"
#include"Enemy.h"
#include "Hud.h"

namespace Engine
{
	class EnemySpawner :
		public IGamePart
	{
	public:

		EnemySpawner(std::vector<std::shared_ptr<Node>>& path, GameDataReference data, std::vector<std::shared_ptr<IGamePart>>& gameParts, Hud* hud);
		virtual ~EnemySpawner();


		// Inherited via IGamePart
		virtual void InputHandler() override;

		virtual void EventHandler(sf::Event event) override;

		virtual void Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts) override;

		virtual void Draw() override;

		virtual sf::FloatRect GetGlobalBounds() override;

		virtual void DealDamage(WeaponType type) override;

	private:
		sf::Clock _clock;
		Hud* _hud;
		int _count{ 0 };
		std::vector<std::shared_ptr<Node>>& _path;
		GameDataReference _data;
		std::vector<std::shared_ptr<IGamePart>>& _gameParts;
	};
}


