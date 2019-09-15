#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include <Game\Components\PlayerMovementComponent.h>
#include <Game\Components\NPCMovementComponent.h>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <string>
#include <chrono>

using namespace Game;

std::string GameBoard::m_houses[19] = {};
int t = 0;

GameBoard::GameBoard()
	: m_player(nullptr)
	, m_dialogBox(nullptr)
{
	// Initialize a reasonable area for the player to explore
	// 3 times screen width rounded to nearest 200
	float board_length = 3800;
	// 200 pixel wide houses gives us up to 19 buildings, potentially less with grocery stores here and there
	// Put a player house in the middle - Element 9
	// Spawn a few places for temp labor that are randomly open or "sorry, no work today" and one school
	// Some higher paying ones will be behind language barrier
	// Have one sketchy visa guy selling a visa for a large sum of money - That'll be the player goal

	// Seed the random generator
	srand(time(NULL));

	//draw the game
	DrawGame(0);

	// Todo eventually - Scenery (sidewalk, sky, streetlamps, road, etc...)
}


GameBoard::~GameBoard()
{

}


void GameBoard::Update() {
	if (GameEngine::GameEngineMain::m_gameTime >= 0.5 && GameEngine::GameEngineMain::m_gameTime <= 0.8 && t < 1) t = 1, DrawGame(1);
	else if (GameEngine::GameEngineMain::m_gameTime > 0.8 && t < 2) t = 2, DrawGame(2);
}

//draw the game in this order - useful for full redraws
void Game::GameBoard::DrawGame(int timeOfDay) {
	DrawBackground(timeOfDay);

	if (timeOfDay == 0) {
		srand(time(NULL));
		// Generate on each side of the player house
		for (int i = 0; i < 19; i++) {
			if (i == 9) {
				m_houses[i] = "PlayerHouse";
			}
			else if (rand() % 100 < 25 && i + 1 != 9 && i + 1 < 19) {
				// 20% chance of spawning a store (also make sure that it doesn't intersect house)
				m_houses[i] = "StoreLeft";
				m_houses[i + 1] = "StoreRight";
				i++;
			}
			else {
				m_houses[i] = "House";
			}
		}
		//draw the randomly generated houses
		for (int i = 0; i < 19; i++) {
			if (m_houses[i] == "House" || m_houses[i] == "PlayerHouse") {
				NewHouse(i);
			}
			else if (m_houses[i] == "StoreLeft") {
				NewStore(i);
			}
		}
		// The stuff gets layered in the order it's added here so add the player last
		CreatePlayer();
	}
	// Generate 4 NPCs
	//for (int i = 0; i < 4; i++) {
		//CreateNPC();
	//}
}

void Game::GameBoard::CreatePlayer()
{
	// Initialize a new player
	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	// Set the spawn location of the player
	m_player->SetPos(sf::Vector2f(3800 / 2, 430.f));
	m_player->SetSize(sf::Vector2f(50.f, 100.f));

	// Add the render component
	// todo sprite and animation
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(m_player->AddComponent<GameEngine::SpriteRenderComponent>());

	// Add the movement component
	m_player->AddComponent<PlayerMovementComponent>();

	render->SetTopLeftRender(false);
	render->SetTexture(GameEngine::eTexture::Player_Right);
	render->SetFillColor(sf::Color::Transparent);
	render->SetTileIndex(0, 0);
	render->SetZLevel(10);
}

void Game::GameBoard::CreateNPC(int x)
{
	// Initialize a new NPC (same as player code with different component)
	GameEngine::Entity* m_npc = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_npc);

	// Set the location of the npc
	m_npc->SetPos(sf::Vector2f((float) x + 50, (rand()%20 + 430.f)));
	m_npc->SetSize(sf::Vector2f(50.f, 100.f));

	// Add the render component
	// todo sprite and animation
	GameEngine::RenderComponent* render = static_cast<GameEngine::RenderComponent*>(m_npc->AddComponent<GameEngine::RenderComponent>());

	render->SetFillColor(sf::Color::Yellow);
	render->SetZLevel(15);

	m_npcs.push_back(m_npc);
	m_npcsx.push_back(x);
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
	renderBase->SetZLevel(1);

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
	renderRoof->SetZLevel(2);

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
	renderDoor->SetZLevel(2);

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
		renderWindow->SetZLevel(2);
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

	// Spawn a NPC in front of the store
	CreateNPC((int)(hPos*200));
}

//display a dialog box. the id corresponds to the text image to use
void Game::GameBoard::ShowDialog(int id) {

	// HideDialog();

	m_dialogBox = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_dialogBox);

	//set the text box position and size
	m_dialogBox->SetPos(sf::Vector2f(m_player->GetPos().x, 250));
	m_dialogBox->SetSize(sf::Vector2f(1000.f, 212.f));

	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(m_dialogBox->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetZLevel(1);
	render->SetFillColor(sf::Color::Transparent);

	switch (id) {
	case 10:
		render->SetTexture(GameEngine::eTexture::Interact_Hint);
	}
}

//close the current dialog box
void Game::GameBoard::HideDialog() {
	GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_dialogBox);
}

void Game::GameBoard::DrawBackground(int timeOfDay) {
	GameEngine::Entity* bg = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bg);

	bg->SetPos(sf::Vector2f(0, -42));
	bg->SetSize(sf::Vector2f(4000, 752));

	GameEngine::SpriteRenderComponent* renderBG = static_cast<GameEngine::SpriteRenderComponent*>(bg->AddComponent<GameEngine::SpriteRenderComponent>());

	renderBG->SetTopLeftRender(true);
	renderBG->SetFillColor(sf::Color::Transparent);

	if (timeOfDay == 0) {
		renderBG->SetZLevel(-3);
		renderBG->SetTexture(GameEngine::eTexture::Background_Day);
	}
	if (timeOfDay == 1) {
		renderBG->SetZLevel(-2);
		renderBG->SetTexture(GameEngine::eTexture::Background_Eve);
	}
	if (timeOfDay == 2) {
		renderBG->SetZLevel(-1);
		renderBG->SetTexture(GameEngine::eTexture::Background_Night);
	}
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

/*void Game::GameBoard::DrawTime(int currentTime) {
	sf::Font font;
	sf::Text text;
	//load the font
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Could not load font" << std::endl;
	}
	text.setString("Hello World!");
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Red);
}*/