#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"


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
	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	m_player->SetPos(sf::Vector2f(640.f, 450.f));
	m_player->SetSize(sf::Vector2f(50.f, 100.f));

	GameEngine::RenderComponent* render = static_cast<GameEngine::RenderComponent*>(m_player->AddComponent<GameEngine::RenderComponent>());

	render->SetFillColor(sf::Color::Red);

}
