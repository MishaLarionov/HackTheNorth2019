#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include <Game\Components\PlayerMovementComponent.h>


using namespace Game;

GameBoard::GameBoard()
	: m_player(nullptr)
	, dialogueBox(nullptr)
	, gameTime(0)
{
	// Initialize a reasonable area for the player to explore
	// 3 times screen width rounded to nearest 200
	float board_length = 3800; 
	// 200 pixel wide houses gives us up to 19 buildings, potentially less with grocery stores here and there
	// Put a player house in the middle
	// Spawn a few places for temp labor that are randomly open or "sorry, no work today" and one school
	// Some higher paying ones will be behind language barrier
	// Have one sketchy visa guy selling a visa for a large sum of money - That'll be the player goal

	// The stuff gets layered in the order it's added here so add the player last
	// Todo add stores to find work
	NewHouse(8);
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
	redBox->SetPos(sf::Vector2f(hPos * 200, 250.f));
	redBox->SetSize(sf::Vector2f(200.f, 400.f));

	// Add the render component
	// todo sprite and animation
	GameEngine::RenderComponent* render = static_cast<GameEngine::RenderComponent*>(redBox->AddComponent<GameEngine::RenderComponent>());

	render->SetFillColor(sf::Color::Blue);
}

//display a dialogue box. the id corresponds to the text image to use
void Game::GameBoard::ShowDialogue(int id) {
	dialogueBox = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(dialogueBox);

	//set the text box position and size
	dialogueBox->SetPos(sf::Vector2f(540.f, 580.f));
	dialogueBox->SetSize(sf::Vector2f(200.f, 100.f));

	GameEngine::RenderComponent* render = static_cast<GameEngine::RenderComponent*>(dialogueBox->AddComponent<GameEngine::RenderComponent>());
	render->SetZLevel(1);
	render->SetFillColor(sf::Color::Transparent);

	switch (id) {
	case -1:
		render->SetTexture(GameEngine::eTexture::Building1Dialogue);
	}
}

//close the current dialogue box
void Game::GameBoard::HideDialogue() {
	GameEngine::GameEngineMain::GetInstance()->RemoveEntity(dialogueBox);
}
