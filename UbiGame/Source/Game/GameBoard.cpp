#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include <Game\Components\PlayerMovementComponent.h>


using namespace Game;

GameBoard::GameBoard()
	: m_player(nullptr)
{
	// The stuff gets layered in the order it's added here so add the player last
	NewBlueBoxForNoReason();
	CreatePlayer();
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

	m_player->SetPos(sf::Vector2f(640.f, 450.f));
	m_player->SetSize(sf::Vector2f(50.f, 100.f));

	// Add the render component
	// todo sprite and animation
	GameEngine::RenderComponent* render = static_cast<GameEngine::RenderComponent*>(m_player->AddComponent<GameEngine::RenderComponent>());

	// Add the movement component
	m_player->AddComponent<PlayerMovementComponent>();

	render->SetFillColor(sf::Color::Red);
}

// Todo remove this whole function (Don't forget .h file)
void Game::GameBoard::NewBlueBoxForNoReason()
{
	GameEngine::Entity* redBox = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(redBox);

	redBox->SetPos(sf::Vector2f(640.f, 450.f));
	redBox->SetSize(sf::Vector2f(50.f, 100.f));

	// Add the render component
	// todo sprite and animation
	GameEngine::RenderComponent* render = static_cast<GameEngine::RenderComponent*>(redBox->AddComponent<GameEngine::RenderComponent>());

	render->SetFillColor(sf::Color::Blue);
}
