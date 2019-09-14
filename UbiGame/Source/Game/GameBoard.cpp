#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include <Game\Components\PlayerMovementComponent.h>
#include <iostream>
#include <chrono>


using namespace Game;

GameBoard::GameBoard()
	: m_player(nullptr)
{
	// Initialize a reasonable area for the player to explore
	// 3 times screen width rounded to nearest 200
	float board_length = 3800; 
	// 200 pixel wide houses gives us up to 19 buildings, potentially less with grocery stores here and there
	// Put a player house in the middle - Element 9
	// Spawn a few places for temp labor that are randomly open or "sorry, no work today" and one school
	// Some higher paying ones will be behind language barrier
	// Have one sketchy visa guy selling a visa for a large sum of money - That'll be the player goal
	std::string houses[19] = {};

	// Seed the random generator
	srand(time(NULL));

	do {
		// Generate on each side of the player house
		for (int i = 0; i < 19; i++) {

			if (i == 9) {
				houses[i] = "PlayerHouse";
			}
			else if (rand() % 100 < 20 && i + 1 != 9 && i + 1 < 19) {
				// 20% chance of spawning a store (also make sure that it doesn't intersect house)
				houses[i] = "StoreLeft";
				houses[i + 1] = "StoreRight";
				i++;
			}
			else {
				houses[i] = "House";
			}
		}
		// Make sure we have at least 2 stores
	} while (false); // todo fix this while (count(houses, houses + 1, "StoreLeft") <= 2);

	// Now we loop again and draw stuff
	for (int i = 0; i < 19; i++) {
		if (houses[i] == "House" || houses[i] == "PlayerHouse") {
			NewHouse(i);
		}
		else if (houses[i] == "StoreLeft") {
			NewStore(i);
		}
	}

	// The stuff gets layered in the order it's added here so add the player last
	CreatePlayer();

	// Todo eventually - Scenery (sidewalk, sky, streetlamps, road, etc...)
}


GameBoard::~GameBoard()
{

}


void GameBoard::Update()
{	
	
}

void Game::GameBoard::CreatePlayer()
{
	// Initialize a new player
	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	m_player->SetPos(sf::Vector2f(3800 / 2, 450.f));
	m_player->SetSize(sf::Vector2f(50.f, 100.f));

	// Add the render component
	// todo sprite and animation
	GameEngine::RenderComponent* render = static_cast<GameEngine::RenderComponent*>(m_player->AddComponent<GameEngine::RenderComponent>());

	// Add the movement component
	m_player->AddComponent<PlayerMovementComponent>();

	render->SetFillColor(sf::Color::Red);
}

// Make a new house. hPos is the house slot on the board
void Game::GameBoard::NewHouse(float hPos)
{
	GameEngine::Entity* redBox = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(redBox);

	// This is about house size
	redBox->SetPos(sf::Vector2f(hPos * 200, 50.f));
	redBox->SetSize(sf::Vector2f(200.f, 400.f));

	// Add the render component
	// todo sprite and animation
	GameEngine::RenderComponent* render = static_cast<GameEngine::RenderComponent*>(redBox->AddComponent<GameEngine::RenderComponent>());

	render->SetTopLeftRender(true);
	render->SetFillColor(sf::Color::Blue);
}

// Make a new store. hPos is the house slot on the board
void Game::GameBoard::NewStore(float hPos)
{
	GameEngine::Entity* redBox = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(redBox);

	// This is about house size
	redBox->SetPos(sf::Vector2f(hPos * 200, 250.f));
	redBox->SetSize(sf::Vector2f(400.f, 200.f));

	// Add the render component
	// todo sprite and animation
	GameEngine::RenderComponent* render = static_cast<GameEngine::RenderComponent*>(redBox->AddComponent<GameEngine::RenderComponent>());
	
	render->SetTopLeftRender(true);
	render->SetFillColor(sf::Color::Green);
}
