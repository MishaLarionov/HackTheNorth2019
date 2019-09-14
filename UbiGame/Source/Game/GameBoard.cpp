#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include <Game\Components\PlayerMovementComponent.h>


using namespace Game;

GameBoard::GameBoard()
	: m_player(nullptr)
{
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
