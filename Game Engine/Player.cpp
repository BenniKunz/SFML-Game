#include "Player.h"
#include <iostream>

Engine::Player::~Player()
{
	std::cout << "Player destructor" << std::endl;
}

void Engine::Player::DealDamage(WeaponType type)
{
	if (type == tankBullet)
	{
		if (_hp - 10 <= 0)
		{
			_hp = 0;
			_lives--;
			PlayerReset();
		}
		else
		{
			_hp -= 10;
		}
	}

	float reduce = _hp / 100.0;
	_healthBar.ChangeHealthBar(reduce);
}

void Engine::Player::CollectItem(ItemType type, int value, IGamePart* gamePart)
{
	_weaponSwitch.play();
	if (type == health && static_cast<float>(value) + _hp > PLAYER_MAX_HP)
	{
		_hp = PLAYER_MAX_HP;
		_healthBar.ChangeHealthBar(1.0);
		Notify(healthCollected, *gamePart);
		return;
	}

	switch (type)
	{
	case gunAmmo:
		_bullets += value;
		Notify(bulletsCollected, *gamePart);
		break;
	case rocketAmmo:
		_rockets += value;
		Notify(rocketsCollected, *gamePart);
		break;

	case health:
		_hp += static_cast<float>(value);
		_healthBar.ChangeHealthBar(_hp / PLAYER_MAX_HP);
		Notify(healthCollected, *gamePart);
		break;

	default:
		break;
	}
}

void Engine::Player::EventHandler(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::L && _clock.getElapsedTime().asSeconds() > _weapon->_shootingDelay)
		{
			_clock.restart();
			if (GetActiveAmmo() > 0)
			{
				switch (_weaponType)
				{
				case gun:
					_gunFire.play();
					break;
				case rocket:
					_rocketFire.play();
					break;
				default:
					break;
				}


				_shot = true;
				this->_weapon->Shoot(_data, _gameParts, GetWeaponPosition(), GetWeaponDirection(), this, 0.0f);
				GetActiveAmmo()--;
				Notify(playerShoot, *this);
			}

		}
		else if (event.key.code == sf::Keyboard::P && this->_weaponType != rocket)
		{
			this->_weapon = std::make_unique<Rocket>();
			this->_weaponType = rocket;
			this->_playerBody.setTexture(this->GetTexture());
			Notify(weaponSwitch, *this);
			_weaponSwitch.play();
		}
		else if (event.key.code == sf::Keyboard::P && this->_weaponType != gun)
		{
			this->_weapon = std::make_unique<Bullet>();
			this->_weaponType = gun;
			this->_playerBody.setTexture(this->GetTexture());
			Notify(weaponSwitch, *this);
			_weaponSwitch.play();
		}
	}
}

void Engine::Player::InputHandler()
{
	float x{ 0.0 };
	float y{ 0.0 };
	_isIdle = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_isIdle = false;
		if (_walkDirection != left)
		{
			_walkDirection = left;
		}
		x = -1.0f;
		y = 0.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_isIdle = false;
		if (_walkDirection != right)
		{
			_walkDirection = right;
		}
		x = 1.0f;
		y = 0.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_isIdle = false;
		if (_walkDirection != up)
		{
			_walkDirection = up;
		}
		x = 0.0f;
		y = -1.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_isIdle = false;
		if (_walkDirection != down)
		{
			_walkDirection = down;
		}
		x = 0.0f;
		y = 1.0f;
	}
	
	_moveDirection = sf::Vector2f(x, y);

}

void Engine::Player::Update(float dt, std::vector<std::shared_ptr<IGamePart>>& _gameParts)
{

	sf::Vector2f tempPos = _playerBody.getPosition();
	SetMoveDirectionForMapBoundaries(tempPos);
	SetMoveDirectionForGamePartBoundaries();
	_position += _moveDirection * _speed * dt;

	_healthBar.SetPosition(sf::Vector2f(_position.x + 10, _position.y));

	//_moveXY *= _speed;

	SetPlayerTextures();
	if (!_isIdle)
	{
		this->_animationManager._animation._texture.setPosition(_position);
		this->_playerBody.setPosition(_position + sf::Vector2f(PLAYER_TEXTURE_OFFSET, PLAYER_TEXTURE_OFFSET));
		/*this->_animationManager._animation._texture.move(_moveXY);
		this->_playerBody.move(_moveXY);*/
		this->_animationManager.Update(dt);
		this->_healthBar.Update(dt, _gameParts);
	}

	for (auto& gamePart : _gameParts)
	{
		if (gamePart.get() == this) { continue; }
		else if (this->_playerBody.getGlobalBounds().intersects(gamePart->GetGlobalBounds()))
		{
			//std::cout << "Player collided" << std::endl;
		}
	}
	_shootCounter.setPosition(_position.x + 90, _position.y);
	if (_shot)
	{

		float y = _weapon->_shootingDelay - _clock.getElapsedTime().asSeconds();


		_shootCounter.setString(std::to_string(y));
	}
	if (_clock.getElapsedTime().asSeconds() > _weapon->_shootingDelay)
	{
		_shot = false;
	}
}

void Engine::Player::Draw()
{
	this->_animationManager.Draw();
	this->_healthBar.Draw();
	this->_data.window.draw(_playerBody);
	if (_shot) { this->_data.window.draw(_shootCounter); };
}

void Engine::Player::SetPlayerTextures()
{
	if (_walkDirection == left)
	{
		this->_animationManager._animation._texture.setTexture(this->_data.assets.GetTexture("playerWalkLeft"));
		this->_playerBody.setTexture(this->GetTexture());
	}
	else if (_walkDirection == right)
	{
		this->_animationManager._animation._texture.setTexture(this->_data.assets.GetTexture("playerWalkRight"));
		this->_playerBody.setTexture(this->GetTexture());
	}
	else if (_walkDirection == up)
	{
		this->_animationManager._animation._texture.setTexture(this->_data.assets.GetTexture("playerWalkUp"));
		this->_playerBody.setTexture(this->GetTexture());
	}
	else if (_walkDirection == down)
	{
		this->_animationManager._animation._texture.setTexture(this->_data.assets.GetTexture("playerWalkDown"));
		this->_playerBody.setTexture(this->GetTexture());
	}
}



int& Engine::Player::GetActiveAmmo()
{
	switch (_weaponType)
	{
	case gun:
		return _bullets;
	case rocket:
		return _rockets;
	default:
		break;
	}
}


sf::Texture& Engine::Player::GetTexture()
{
	if (_walkDirection == left)
	{
		switch (_weaponType)
		{
		case gun:
		{
			return this->_data.assets.GetTexture("playerBodyLeft");
			break;
		}
		case rocket:
		{
			return this->_data.assets.GetTexture("playerRocketLeft");
			break;
		}
		default:
			break;
		}

	}
	else if (_walkDirection == right)
	{
		switch (_weaponType)
		{
		case gun:
		{
			return this->_data.assets.GetTexture("playerBodyRight");
			break;
		}
		case rocket:
		{
			return this->_data.assets.GetTexture("playerRocketRight");
			break;
		}
		default:
			break;
		}
	}
	else if (_walkDirection == up)
	{
		switch (_weaponType)
		{
		case gun:
		{
			return this->_data.assets.GetTexture("playerBodyUp");
			break;
		}
		case rocket:
		{
			return this->_data.assets.GetTexture("playerRocketUp");
			break;
		}
		default:
			break;
		}
	}
	else if (_walkDirection == down)
	{
		switch (_weaponType)
		{
		case gun:
		{
			return this->_data.assets.GetTexture("playerBodyDown");
			break;
		}
		case rocket:
		{
			return this->_data.assets.GetTexture("playerRocketDown");
			break;
		}
		default:
			break;
		}
	}
}

sf::Vector2f Engine::Player::GetWeaponDirection()
{
	switch (_walkDirection)
	{
	case left:
		return sf::Vector2f(-1, 0);
		break;
	case right:
		return sf::Vector2f(1, 0);
		break;
	case up:
		return sf::Vector2f(0, -1);
		break;
	case down:
		return sf::Vector2f(0, 1);
		break;
	default:
		break;
	}
}

sf::Vector2f Engine::Player::GetWeaponPosition()
{
	int posX = this->_playerBody.getPosition().x;
	int posY = this->_playerBody.getPosition().y;


	switch (_walkDirection)
	{
	case left:
		return sf::Vector2f(posX, posY + this->_playerBody.getGlobalBounds().height / 2);
		break;
	case right:
		return sf::Vector2f(posX + this->_playerBody.getGlobalBounds().width, posY + this->_playerBody.getGlobalBounds().height / 2);
		break;
	case up:
		return sf::Vector2f(posX + this->_playerBody.getGlobalBounds().width / 2, posY);
		break;
	case down:
		return sf::Vector2f(posX + this->_playerBody.getGlobalBounds().width / 2, posY + this->_playerBody.getGlobalBounds().height);
		break;
	default:
		break;
	}
}

void Engine::Player::SetMoveDirectionForMapBoundaries(sf::Vector2f tempPos)
{
	tempPos += _moveDirection;
	if (tempPos.x <= 0 && tempPos.y <= 0
		|| tempPos.x <= 0 && tempPos.y >= (MAP_HEIGHT - 1) * TILE_HEIGHT
		|| tempPos.y <= 0 && tempPos.x >= (MAP_WIDTH - 1) * TILE_WIDTH
		|| tempPos.x >= (MAP_WIDTH - 1) * TILE_WIDTH && tempPos.y >= (MAP_HEIGHT - 1) * TILE_HEIGHT)
	{
		_moveDirection = sf::Vector2f(0, 0);
	}
	else if (tempPos.x <= 0 || tempPos.x >= (MAP_WIDTH - 1) * TILE_WIDTH)
	{
		_moveDirection = sf::Vector2f(0, _moveDirection.y);
	}
	else if (tempPos.y <= 0 || tempPos.y >= (MAP_HEIGHT - 1) * TILE_HEIGHT)
	{
		_moveDirection = sf::Vector2f(_moveDirection.x, 0);
	}
}

void Engine::Player::SetMoveDirectionForGamePartBoundaries()
{
	sf::Sprite tempBody = _playerBody;
	tempBody.move(_moveDirection);
	for (auto gamePart : _gameParts)
	{
		if (gamePart.get() == this) { continue; }
		if (tempBody.getGlobalBounds().intersects(gamePart->GetGlobalBounds()))
		{
			_moveDirection = sf::Vector2f(0, 0);
		}
	}
}

void Engine::Player::PlayerReset()
{
	_hp = 100;
	_healthBar.ChangeHealthBar(1.0);
	_position = sf::Vector2f(PLAYER_START_POSX, PLAYER_START_POSY);
	this->_animationManager._animation._texture.setPosition(_position);
	this->_playerBody.setPosition(_position + sf::Vector2f(PLAYER_TEXTURE_OFFSET, PLAYER_TEXTURE_OFFSET));
	_data.view.reset(sf::FloatRect(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT));
	_data.window.setView(_data.view);
}

int& Engine::Player::GetLives()
{
	return this->_lives;
}

void Engine::Player::ReduceLives()
{
	if (_lives >= 1)
		_lives--;
}

void Engine::Player::Display()
{
}

void Engine::Player::RegisterObserver(IObserver* observer)
{
	_observerList.push_back(observer);
}

void Engine::Player::RemoveObserver(IObserver* observer)
{
	_observerList.erase(std::remove(_observerList.begin(), _observerList.end(), observer), _observerList.end());
}

void Engine::Player::Notify(GameEvent gameEvent, IGamePart& gamePart)
{
	for (auto observer : _observerList)
	{
		observer->OnNotify(gameEvent, gamePart);
	}
}
