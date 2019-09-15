#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include <Game\Components\PlayerMovementComponent.h>
#include <Game\Components\NPCMovementComponent.h>
#include <iostream>
#include <chrono>


using namespace Game;

GameBoard::GameBoard()
	: m_player(nullptr)
	, m_dialogBox(nullptr)
	//, gameTime(0)
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

	//draw the background
	DrawBackground();

	// Generate on each side of the player house
	for (int i = 0; i < 19; i++) {

		if (i == 9) {
			houses[i] = "PlayerHouse";
		}
		else if (rand() % 100 < 25 && i + 1 != 9 && i + 1 < 19) {
			// 20% chance of spawning a store (also make sure that it doesn't intersect house)
			houses[i] = "StoreLeft";
			houses[i + 1] = "StoreRight";
			i++;
		}
		else {
			houses[i] = "House";
		}
	}

	// Now we loop again and draw stuff
	srand(time(NULL));
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

	// Generate 4 NPCs
	for (int i = 0; i < 4; i++) {
		CreateNPC();
	}

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

	// Set the spawn location of the npc
	m_player->SetPos(sf::Vector2f(3800 / 2, 435.f));
	m_player->SetSize(sf::Vector2f(50.f, 100.f));

	// Add the render component
	// todo sprite and animation
	GameEngine::RenderComponent* render = static_cast<GameEngine::RenderComponent*>(m_player->AddComponent<GameEngine::RenderComponent>());

	// Add the movement component
	m_player->AddComponent<PlayerMovementComponent>();

	render->SetFillColor(sf::Color::Red);
}

void Game::GameBoard::CreateNPC()
{
	// Initialize a new NPC (same as player code with different component)
	GameEngine::Entity* m_npc = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_npc);

	int ranX = (int) ((3800.f / 19) * (rand() % 20 + 1));

	// Set the location of the npc
	m_npc->SetPos(sf::Vector2f((float) ranX, (rand()%10 + 450.f)));
	m_npc->SetSize(sf::Vector2f(50.f, 100.f));

	// Add the render component
	// todo sprite and animation
	GameEngine::RenderComponent* render = static_cast<GameEngine::RenderComponent*>(m_npc->AddComponent<GameEngine::RenderComponent>());

	render->SetFillColor(sf::Color::Yellow);

	m_npcs.push_back(m_npc);
	m_npcsx.push_back(ranX);
}

// Make a new house. hPos is the house slot on the board
void Game::GameBoard::NewHouse(float hPos)
{

	// Alright y'all, we're gonna generate a whole new house now u ready?
	GameEngine::Entity* baseTile = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(baseTile);
	// This is about house size
	baseTile->SetPos(sf::Vector2f(hPos * 200, 50.f));
	baseTile->SetSize(sf::Vector2f(200.f, 400.f));
	// Add the render component
	GameEngine::SpriteRenderComponent* renderBase = static_cast<GameEngine::SpriteRenderComponent*>(baseTile->AddComponent<GameEngine::SpriteRenderComponent>());
	renderBase->SetTopLeftRender(true);
	renderBase->SetFillColor(sf::Color::Transparent);
	renderBase->SetTexture(GameEngine::eTexture::BottomTiles);
	renderBase->SetTileIndex(sf::Vector2i(rand() % 3, 0));

	// This is to make the roof
	GameEngine::Entity* roofTile = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(roofTile);
	// Roof size
	roofTile->SetPos(sf::Vector2f(hPos * 200, 50.f));
	roofTile->SetSize(sf::Vector2f(200.f, 43.f));
	// Add the render component
	GameEngine::SpriteRenderComponent* renderRoof = static_cast<GameEngine::SpriteRenderComponent*>(roofTile->AddComponent<GameEngine::SpriteRenderComponent>());
	renderRoof->SetTopLeftRender(true);
	renderRoof->SetFillColor(sf::Color::Transparent);
	renderRoof->SetTexture(GameEngine::eTexture::RoofTiles);
	renderRoof->SetTileIndex(sf::Vector2i(rand() % 3, 0));

	// This is the door
	GameEngine::Entity* door = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(door);
	// Door size/pos, will render at center
	door->SetPos(sf::Vector2f((hPos * 200) + 100, 370.f));
	door->SetSize(sf::Vector2f(70.f, 110.f));
	// Add the render component
	GameEngine::SpriteRenderComponent* renderDoor = static_cast<GameEngine::SpriteRenderComponent*>(door->AddComponent<GameEngine::SpriteRenderComponent>());
	renderDoor->SetTopLeftRender(false);
	renderDoor->SetFillColor(sf::Color::Transparent);
	renderDoor->SetTexture(GameEngine::eTexture::Doors);
	renderDoor->SetTileIndex(sf::Vector2i(rand() % 2, 0));

	// Draw the four windows
	int windowStyle = rand() % 2;
	for (int i = 1; i <= 4; i++) {
		GameEngine::Entity* windowTile = new GameEngine::Entity();
		GameEngine::GameEngineMain::GetInstance()->AddEntity(windowTile);
		// Window size/pos
		if (i <= 2) {
			windowTile->SetPos(sf::Vector2f((hPos * 200) + 67 * (i % 2 + 1), 150.f));
		}
		else {
			windowTile->SetPos(sf::Vector2f((hPos * 200) + 67 * (i % 2 + 1), 225.f));
		}
		windowTile->SetSize(sf::Vector2f(60, 70));

		// Render component
		GameEngine::SpriteRenderComponent* renderWindow = static_cast<GameEngine::SpriteRenderComponent*>(windowTile->AddComponent<GameEngine::SpriteRenderComponent>());
		renderWindow->SetTopLeftRender(false);
		renderWindow->SetFillColor(sf::Color::Transparent);
		renderWindow->SetTexture(GameEngine::eTexture::Windows);
		renderWindow->SetTileIndex(sf::Vector2i(windowStyle, 0));
	}
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
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(redBox->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetTopLeftRender(true);
	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::Store);
}

//display a dialog box. the id corresponds to the text image to use
void Game::GameBoard::ShowDialog(int id) {
	m_dialogBox = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_dialogBox);

	//set the text box position and size
	m_dialogBox->SetPos(sf::Vector2f(540.f, 580.f));
	m_dialogBox->SetSize(sf::Vector2f(200.f, 100.f));

	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(m_dialogBox->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetZLevel(1);
	render->SetFillColor(sf::Color::Transparent);

	 switch (id) {
	 case 10:
		render->SetTexture(GameEngine::eTexture::Store);
	 }
}

//close the current dialog box
void Game::GameBoard::HideDialog() {
	GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_dialogBox);
}

void Game::GameBoard::DrawBackground() {
	GameEngine::Entity* bg = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bg);

	bg->SetPos(sf::Vector2f(0,-42));
	bg->SetSize(sf::Vector2f(4000,752));

	GameEngine::SpriteRenderComponent* renderBG = static_cast<GameEngine::SpriteRenderComponent*>(bg->AddComponent<GameEngine::SpriteRenderComponent>());

	renderBG->SetTopLeftRender(true);
	renderBG->SetFillColor(sf::Color::Transparent);
	//renderEnt->SetZLevel(-1);
	renderBG->SetTexture(GameEngine::eTexture::Background);
}

void Game::GameBoard::UpdateValues(int caseNum)
{
	switch (caseNum)
	{
	case 1:
		language += 10;
		money -= 50;
		break;
	case 2:
		language = 0;
		money += 50;
		break;
	case 3:
		language += 10;
		money -= 50;
		break;
	}
}