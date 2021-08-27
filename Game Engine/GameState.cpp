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
#include "ItemSpawner.h"

Engine::GameState::GameState(GameDataReference data)
	:_data{ data }, _hudPtr{nullptr}
{

}

Engine::GameState::~GameState()
{
	_hudPtr = nullptr;
	std::cout << "GameState Destructor" << std::endl;
	
}

void Engine::GameState::Init()
{
	LoadAssets(this->_data);
	this->_data->assets.PlayMusic(_music, MAIN_MENU_MUSIC, true);

	_map.load("Resources/tiles.png", sf::Vector2u(TILE_WIDTH, TILE_HEIGHT), _levelTest, MAP_WIDTH, MAP_HEIGHT);

	std::shared_ptr<Graph> graph = std::make_shared<Graph>(this->_levelTest);
	graph->makeGraph();

	std::shared_ptr<PauseButton> pauseButton = std::make_shared<PauseButton>(300, 100, _data, "pauseButton");

	std::shared_ptr<BreadthFirstSearch> bfs = std::make_shared<BreadthFirstSearch>(graph, "bfs");
	this->_path = bfs->CalculatePath();
	
	_player = std::make_shared<Player>(sf::Vector2f{ 300, 800 }, "playerWalkUp", _data, _gameParts);
	std::shared_ptr<ItemSpawner> itemSpawner = std::make_shared<ItemSpawner>(_player, _data, _gameParts);
	std::shared_ptr<Hud> _hud = std::make_shared<Hud>(_data, _player);
	_hudPtr = _hud.get();
	std::shared_ptr<EnemySpawner> enemySpawner = std::make_shared<EnemySpawner>(_path, _data, _gameParts, _hudPtr);


	_gameParts.push_back(enemySpawner);
	_gameParts.push_back(itemSpawner);
	_gameParts.push_back(_player);
	_menuParts.push_back(_hud);
	_menuParts.push_back(pauseButton);

}

void Engine::LoadAssets(GameDataReference _data)
{
	_data->assets.LoadTexture("backButton", PAUSE_BACK_BUTTON);
	_data->assets.LoadTexture("pauseButton", GAME_MENU_PAUSE_BUTTON);
	_data->assets.LoadTexture("enemyTexture", ENEMY_TEXTURE);
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

	_data->assets.LoadFont("gameFont", GAME_FONT);

	_data->assets.LoadTexture("ammoTexture", AMMO_TEXTURE);
	_data->assets.LoadTexture("hpTexture", HP_TEXTURE);
	_data->assets.LoadTexture("speedTexture", SPEED_TEXTURE);
}

void Engine::GameState::InputHandler()
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
		gamePart->InputHandler(event);
	}

	for (auto& menuPart : _menuParts)
	{
		menuPart->InputHandler(event);
	}
}

void Engine::GameState::Update(float dt)
{

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
}

void Engine::GameState::Draw(float dt)
{
	this->_data->window.clear(sf::Color::Red);

	this->_data->window.draw(this->_backgroundTexture);
	
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