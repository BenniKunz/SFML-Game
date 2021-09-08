#include "GameState.h"
#include "Parameters.h"
#include "PauseButton.h"
#include <iostream>
#include "Graph.h"
#include "BreadthFirstSearch.h"
#include "Enemy.h"
#include "Hud.h"
#include "Player.h"
#include "Game.h"
#include "GameOverState.h"
#include "Item.h"
#include "House.h"
#include "Tank.h"

Engine::GameState::GameState(GameDataReference data)
	:_data{ data }, _hudPtr{ nullptr }
{
	
}

Engine::GameState::~GameState()
{
	_hudPtr = nullptr;
	std::cout << "GameState Destructor" << std::endl;
}

void Engine::GameState::Init()
{
	LoadAssets();
	//this->_data->assets.PlayMusic(_music, MAIN_MENU_MUSIC, true);

	_map.load("Resources/tiles.png", sf::Vector2u(TILE_WIDTH, TILE_HEIGHT), _levelTest, MAP_WIDTH, MAP_HEIGHT);

	std::unique_ptr<Graph> graph = std::make_unique<Graph>(this->_levelTest);
	graph->makeGraph();


	std::unique_ptr<BreadthFirstSearch> bfs = std::make_unique<BreadthFirstSearch>(std::move(graph), "bfs");
	this->_path = bfs->CalculatePath();

	_player = std::make_shared<Player>(sf::Vector2f{ PLAYER_START_POSX, PLAYER_START_POSY }, "playerWalkUp", _data, _gameParts);
	std::shared_ptr<House> startPoint = std::make_shared<House>(_player, sf::Vector2f(100, 100), "humvee", _data, _gameParts);

	std::shared_ptr<Hud> _hud = std::make_shared<Hud>(_data, _player);
	_hudPtr = _hud.get();
	std::shared_ptr<EnemySpawner> enemySpawner = std::make_shared<EnemySpawner>(_path, _data, _gameParts, _hudPtr);
	
	std::shared_ptr<PauseButton> pauseButton = std::make_shared<PauseButton>(300, 100, _data, "pauseButton");

	SpawnTanks();
	SpawnHouses();

	_gameParts.push_back(startPoint);
	_gameParts.push_back(enemySpawner);
	_gameParts.push_back(_player);
	_menuParts.push_back(_hud);
	_menuParts.push_back(pauseButton);

}

void Engine::GameState::LoadAssets()
{
	_data->assets.LoadTexture("backButton", PAUSE_BACK_BUTTON);
	_data->assets.LoadTexture("pauseButton", GAME_MENU_PAUSE_BUTTON);

	_data->assets.LoadTexture("enemyBodyUp", ENEMY_BODY_UP);
	_data->assets.LoadTexture("enemyBodyDown", ENEMY_BODY_DOWN);
	_data->assets.LoadTexture("enemyBodyRight", ENEMY_BODY_RIGHT);
	_data->assets.LoadTexture("enemyBodyLeft", ENEMY_BODY_LEFT);

	_data->assets.LoadTexture("enemyWalkUp", ENEMY_WALK_UP);
	_data->assets.LoadTexture("enemyWalkRight", ENEMY_WALK_RIGHT);
	_data->assets.LoadTexture("enemyWalkLeft", ENEMY_WALK_LEFT);
	_data->assets.LoadTexture("enemyWalkDown", ENEMY_WALK_DOWN);

	_data->assets.LoadTexture("tankTower", TANK_TOWER);
	_data->assets.LoadTexture("tankBase", TANK_BASE);
	_data->assets.LoadTexture("tankBroken", TANK_BROKEN);
	_data->assets.LoadTexture("humvee", HUMVEE_TEXTURE);

	_data->assets.LoadTexture("house", HOUSE_TEXTURE);

	_data->assets.LoadTexture("playerWalkUp", PLAYER_WALK_UP);
	_data->assets.LoadTexture("playerWalkRight", PLAYER_WALK_RIGHT);
	_data->assets.LoadTexture("playerWalkLeft", PLAYER_WALK_LEFT);
	_data->assets.LoadTexture("playerWalkDown", PLAYER_WALK_DOWN);

	_data->assets.LoadTexture("playerBodyUp", PLAYER_BODY_UP);
	_data->assets.LoadTexture("playerBodyRight", PLAYER_BODY_RIGHT);
	_data->assets.LoadTexture("playerBodyLeft", PLAYER_BODY_LEFT);
	_data->assets.LoadTexture("playerBodyDown", PLAYER_BODY_DOWN);

	_data->assets.LoadTexture("playerRocketUp", PLAYER_ROCKET_UP);
	_data->assets.LoadTexture("playerRocketRight", PLAYER_ROCKET_RIGHT);
	_data->assets.LoadTexture("playerRocketLeft", PLAYER_ROCKET_LEFT);
	_data->assets.LoadTexture("playerRocketDown", PLAYER_ROCKET_DOWN);

	_data->assets.LoadTexture("bulletTexture", BULLET_TEXTURE);
	_data->assets.LoadTexture("rocketTexture", ROCKET_TEXTURE);
	_data->assets.LoadTexture("tankBulletTexture", TANK_BULLET_TEXTURE);

	_data->assets.LoadTexture("healthBarRed", HEALTH_BAR_RED);
	_data->assets.LoadTexture("healthBarGreen", HEALTH_BAR_GREEN);

	_data->assets.LoadFont("gameFont", GAME_FONT);

	_data->assets.LoadTexture("ammoTexture", AMMO_TEXTURE);
	_data->assets.LoadTexture("hpTexture", HP_TEXTURE);
	_data->assets.LoadTexture("speedTexture", SPEED_TEXTURE);

	_data->assets.LoadTexture("gunTexture", GUN_TEXTURE);
	_data->assets.LoadTexture("rocketLauncherTexture", ROCKETLAUNCHER_TEXTURE);

	_data->assets.LoadTexture("hudTable", HUD_TABLE);
	_data->assets.LoadTexture("ammoIcon", AMMO_ICON);
	_data->assets.LoadTexture("hpIcon", HP_ICON);
}

void Engine::GameState::SpawnTanks()
{
	std::array<sf::Vector2f, 28> array
	{
		sf::Vector2f(900, 600),sf::Vector2f(1400, 1000),sf::Vector2f(1600, 300),sf::Vector2f(1900, 500),sf::Vector2f(2200, 600),
		sf::Vector2f(1600, 1200),sf::Vector2f(600, 1400),sf::Vector2f(400, 1000),sf::Vector2f(2500, 800),sf::Vector2f(2000, 1100),
		sf::Vector2f(2400, 1000),sf::Vector2f(1400, 1600),sf::Vector2f(1800, 1800),sf::Vector2f(2000, 1400),sf::Vector2f(3300, 800),
		sf::Vector2f(2800, 800),sf::Vector2f(650, 1100),sf::Vector2f(400, 1000),sf::Vector2f(200, 1400),sf::Vector2f(1200, 1200),
		sf::Vector2f(2800, 400), sf::Vector2f(3200, 400), sf::Vector2f(900, 1600), sf::Vector2f(1400, 100),sf::Vector2f(1400, 750),
		sf::Vector2f(130, 830), sf::Vector2f(3000, 900),sf::Vector2f(3100, 400),
	};

	for (size_t i = 0; i < array.size(); i++)
	{
		std::shared_ptr<Tank> tank = std::make_shared<Tank>(array[i], "tankBase", _data, _gameParts, _player);
		_gameParts.push_back(tank);
	}
}

void Engine::GameState::SpawnHouses()
{
	std::array<sf::Vector2f, 7> array
	{
		sf::Vector2f(800, 300),sf::Vector2f(1400, 2000),sf::Vector2f(3200, 1400),sf::Vector2f(2200, 1600),sf::Vector2f(2200, 300),
		sf::Vector2f(300, 1800),sf::Vector2f(3100, 1800)
	};
	for (size_t i = 0; i < array.size(); i++)
	{
		std::shared_ptr<House> house = std::make_shared<House>(_player, array[i], "house", _data, _gameParts);
		_gameParts.push_back(house);
	}
}

void Engine::GameState::InputHandler(float dt)
{

	if (_player->GetLives() <= 0)
	{
		this->_data->stateMachine.AddState(StateReference(std::make_unique<GameOverState>(this->_data)), true);

	}
	sf::Event event;

	std::vector<std::shared_ptr<IGamePart>> gamePartsArr(_gameParts.size());
	std::copy(_gameParts.begin(), _gameParts.end(), gamePartsArr.begin());

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			for (auto& gamePart : gamePartsArr)
			{
				gamePart->EventHandler(event);
			}
		}
	}
	for (auto& gamePart : gamePartsArr)
	{
		gamePart->InputHandler(dt);
	}

	for (auto& menuPart : _menuParts)
	{
		menuPart->InputHandler();
	}
}

void Engine::GameState::Update(float dt)
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(this->_data->window);
	sf::Vector2f worldPos = this->_data->window.mapPixelToCoords(pixelPos);
	std::cout << worldPos.x << "//" << worldPos.y << std::endl;

	SetSFMLView();

	std::vector<std::shared_ptr<IGamePart>> gamePartsArr(_gameParts.size());
	std::copy(_gameParts.begin(), _gameParts.end(), gamePartsArr.begin());

	for (auto& gamePart : gamePartsArr)
	{
		gamePart->Update(dt, _gameParts);
	}

	for (auto& menuPart : _menuParts)
	{
		menuPart->Update(dt);
	}

	//remove GameParts which are marked as "removed"
	std::vector<std::shared_ptr<IGamePart>>::iterator it = _gameParts.begin();
	while (it != _gameParts.end())
	{
		if ((*it)->_removed == true)
		{
			it = _gameParts.erase(it);
		}
		else
		{
			it++;
		}
	}

	/*for (auto& gamePart : _gameParts)
	{
		auto itr = _gameParts.begin();
		while (itr != _gameParts.end())
		{
			if ((*itr)->_removed == true)
			{
				itr = _gameParts.erase(itr);
			}
			else
			{
				++itr;
			}
		}
	}*/

}

void Engine::GameState::SetSFMLView()
{
	if (_player->GetPlayerPosition().x - this->_data->view.getSize().x / 2 < 0 && _player->GetPlayerPosition().y - this->_data->view.getSize().y / 2 < 0
		|| _player->GetPlayerPosition().x - this->_data->view.getSize().x / 2 < 0 && _player->GetPlayerPosition().y + this->_data->view.getSize().y / 2 > MAP_HEIGHT * TILE_HEIGHT
		|| _player->GetPlayerPosition().x + this->_data->view.getSize().x / 2 > MAP_WIDTH * TILE_WIDTH && _player->GetPlayerPosition().y - this->_data->view.getSize().y / 2 < 0
		|| _player->GetPlayerPosition().x + this->_data->view.getSize().x / 2 > MAP_WIDTH * TILE_WIDTH && _player->GetPlayerPosition().y + this->_data->view.getSize().y / 2 > MAP_HEIGHT * TILE_HEIGHT)
	{
		
	}
	else if (_player->GetPlayerPosition().x - this->_data->view.getSize().x / 2 < 0)
	{
		this->_data->view.setCenter(this->_data->view.getSize().x / 2, _player->GetPlayerPosition().y);
		_data->window.setView(_data->view);
	}
	else if (_player->GetPlayerPosition().x + this->_data->view.getSize().x / 2 > MAP_WIDTH * TILE_WIDTH)
	{
		this->_data->view.setCenter(MAP_WIDTH * TILE_WIDTH - this->_data->view.getSize().x / 2, _player->GetPlayerPosition().y);
		_data->window.setView(_data->view);
	}
	else if (_player->GetPlayerPosition().y - this->_data->view.getSize().y / 2 < 0)
	{
		this->_data->view.setCenter(_player->GetPlayerPosition().x, this->_data->view.getSize().y / 2);
		_data->window.setView(_data->view);	
	}
	else if (_player->GetPlayerPosition().y + this->_data->view.getSize().y / 2 > MAP_HEIGHT * TILE_HEIGHT)
	{
		this->_data->view.setCenter(_player->GetPlayerPosition().x, MAP_HEIGHT * TILE_HEIGHT - this->_data->view.getSize().y / 2);
		_data->window.setView(_data->view);
	}
	else
	{
		this->_data->view.setCenter(_player->GetPlayerPosition());
		_data->window.setView(_data->view);
	}
}

void Engine::GameState::Draw(float dt)
{
	this->_data->window.clear(sf::Color::Red);

	this->_data->window.draw(this->_map);

	for (auto& gamePart : _gameParts)
	{
		if (!gamePart->_removed)
		{
			gamePart->Draw(dt);
		}
	}

	for (auto& menuPart : _menuParts)
	{
		menuPart->Draw(dt);
	}

	this->_data->window.display();
}