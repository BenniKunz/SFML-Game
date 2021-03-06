#pragma once
#include "Sprite.h"
#include "Animation.h"
#include "AnimationManager.h"
#include "ControllerStrategy.h"
#include "Bullet.h"
#include "Rocket.h"
#include "Parameters.h"
#include "IGamePart.h"
#include "WalkDirection.h"
#include "WeaponType.h"
#include "IObserver.h"
#include "ISubject.h"
#include "ItemType.h"
#include "HealthBar.h"

namespace Engine
{
	class Player :
		public Sprite, public ControllerStrategy, public ISubject
	{
	public:
		Player(sf::Vector2f position, std::string textureName, GameData& data, std::vector<std::shared_ptr<IGamePart>>& gameParts)
			: Sprite(position, textureName, data, gameParts),
			_animation(_textureName, 1, 7, _data, _position), _animationManager(_animation, _data),
			_healthBar(_position, "healthBarRed", _data, _gameParts)
		{
			this->_weapon = std::make_unique<Bullet>();
			this->_playerBody.setTexture(this->_data.assets.GetTexture("playerBodyUp"));
			this->_playerBody.setPosition(_position.x + PLAYER_TEXTURE_OFFSET, _position.y + PLAYER_TEXTURE_OFFSET);
			_walkDirection = up;
			_weaponType = gun;
			_layer = player;

			_shootCounter.setFont(this->_data.assets.GetFont("gameFont"));
			_shootCounter.setFillColor(sf::Color::Red);
			_shootCounter.setCharacterSize(20);
			_shootCounter.setPosition(_position.x + 90, _position.y);

			_rocketFire.setBuffer(this->_data.assets.GetSound("rocketFire"));
			_gunFire.setBuffer(this->_data.assets.GetSound("gunFire"));
			_weaponSwitch.setBuffer(this->_data.assets.GetSound("weaponSwitch"));
			_playerHit.setBuffer(this->_data.assets.GetSound("playerHit"));
		}

		virtual ~Player();

		void DealDamage(WeaponType type);
		void CollectItem(ItemType type, int value, IGamePart* gamePart);
		int& GetActiveAmmo();
		WeaponType GetActiveWeapon() { return _weaponType; };
		sf::Vector2f GetPlayerPosition() { return _playerBody.getPosition(); }
		sf::Vector2f GetPlayerShootAtPos() { return sf::Vector2f(_playerBody.getPosition().x + _playerBody.getGlobalBounds().width / 2, _playerBody.getPosition().y + _playerBody.getGlobalBounds().height / 2); }
		int& GetLives();
		void ReduceLives();
		HealthBar _healthBar;

		// Inherited via ISubject
		virtual void RegisterObserver(IObserver* observer) override;

		virtual void RemoveObserver(IObserver* observer) override;

		virtual void Notify(GameEvent gameEvent, IGamePart& gamePart) override;

		// Inherited via Sprite
		virtual sf::FloatRect GetGlobalBounds() override { return this->_playerBody.getGlobalBounds(); };

	private:

		// Inherited via Sprite
		virtual void EventHandler(sf::Event event) override;
		virtual void InputHandler() override;
		virtual void Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts) override;
		void SetPlayerTextures();
		virtual void Draw() override;


		std::vector<IObserver*> _observerList;
		Animation _animation;
		AnimationManager _animationManager;
		sf::Sprite _playerBody;
		WalkDirection _walkDirection;
		WeaponType _weaponType;
		sf::Clock _clock;
		sf::Vector2f _moveDirection;
		sf::Text _shootCounter;
		sf::Sound _weaponSwitch;
		sf::Sound _gunFire;
		sf::Sound _rocketFire;
		sf::Sound _playerHit;

		bool _shot{ false };
		bool _isIdle{ true };
		int _lives = 4;
		int _bullets = 5;
		int _rockets = 2;
		float _speed = 120.0;
		float _hp = 100.0;

		sf::Texture& GetTexture();
		sf::Vector2f GetWeaponDirection();
		sf::Vector2f GetWeaponPosition();
		void SetMoveDirectionForMapBoundaries(sf::Vector2f tempPos);
		void SetMoveDirectionForGamePartBoundaries();
		void PlayerReset();

		// Inherited via ControllerStrategy
		virtual void Display() override;
	};
}


