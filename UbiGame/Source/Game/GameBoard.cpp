#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine\EntitySystem\Components\AnimationComponent.h"
#include <Game\Components\PlayerMovementComponent.h>
#include <Game\Components\NPCMovementComponent.h>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <exception> 

using namespace Game;

std::string GameBoard::m_houses[19] = {};
int t = 0;
GameEngine::Entity* bg0;
GameEngine::Entity* bg1;
GameEngine::Entity* bg2;

GameBoard::GameBoard()
	: m_player(nullptr)
	, m_dialogBox(nullptr)
	//, gameTime(0)
{
	inDialog = false;
	inResp = false;
	language = 0;
	money = 100;
	
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
	DrawGame(0, true);

	// Todo eventually - Scenery (sidewalk, sky, streetlamps, road, etc...)
}


GameBoard::~GameBoard()
{

}


void GameBoard::Update() {
	if (GameEngine::GameEngineMain::m_gameTime >= 1.0 && t == 2) GameEngine::GameEngineMain::m_gameTime = 0.0, t = 0, NextDay();
	else if (GameEngine::GameEngineMain::m_gameTime >= 0.5 && GameEngine::GameEngineMain::m_gameTime <= 0.8 && t < 1) t = 1, DrawGame(1, false);
	else if (GameEngine::GameEngineMain::m_gameTime > 0.8 && t < 2) t = 2, DrawGame(2, false);
}

//draw the game in this order - useful for full redraws
void Game::GameBoard::DrawGame(int timeOfDay, bool newGame) {
	DrawBackground(timeOfDay);

	if (timeOfDay == 0 && newGame) {
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

	//render->SetTopLeftRender(false);
	render->SetTexture(GameEngine::eTexture::Player_Right);
	render->SetFillColor(sf::Color::Transparent);
	//render->SetTileIndex(0, 0);
	render->SetTileIndex(0, 0);
	render->SetZLevel(10);
	// Add the movement and animation components
	m_player->AddComponent<PlayerMovementComponent>();
	m_player->AddComponent<GameEngine::AnimationComponent>();

}

void Game::GameBoard::CreateNPC(int x)
{
	// Initialize a new NPC (same as player code with different component)
	GameEngine::Entity* m_npc = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_npc);

	// Set the location of the npc
	m_npc->SetPos(sf::Vector2f((float) x + 50, (rand()%10 + 450.f)));
	m_npc->SetSize(sf::Vector2f(50.f, 100.f));

	// Add the render component
	// todo sprite and animation
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(m_npc->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetFillColor(sf::Color::Transparent);
	render->SetZLevel(15);
	render->SetTileIndex(0, 0);
	render->SetTexture(GameEngine::eTexture::Npc_Right);

	/*GameEngine::SpriteRenderComponent* renderNPC = static_cast<GameEngine::SpriteRenderComponent*>(m_npc->AddComponent<GameEngine::SpriteRenderComponent>());
	renderNPC->SetTopLeftRender(true);
	renderNPC->SetFillColor(sf::Color::Transparent);
	renderNPC->SetTexture(GameEngine::eTexture::NPC);
	renderNPC->SetTileIndex(sf::Vector2i(rand() % 4, 0));
	renderNPC->SetZLevel(15);*/

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

	//HideDialog();

	if (!inDialog) {

		m_dialogBox = new GameEngine::Entity();
		GameEngine::GameEngineMain::GetInstance()->AddEntity(m_dialogBox);

		//set the text box position and size
		m_dialogBox->SetPos(sf::Vector2f(m_player->GetPos().x, 250));
		m_dialogBox->SetSize(sf::Vector2f(550.f, 212.f));

		GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(m_dialogBox->AddComponent<GameEngine::SpriteRenderComponent>());
		
		render->SetFillColor(sf::Color::Transparent);
		render->SetZLevel(4);

		switch (id) {
		case 10:
			render->SetTexture(GameEngine::eTexture::Shop_Work);
			if (language <= 9) {
				render->SetTileIndex(sf::Vector2i(0, 0));
			}
			else if (language >= 10 && language <= 19) {
				render->SetTileIndex(sf::Vector2i(1, 0));
			}
			else {
				render->SetTileIndex(sf::Vector2i(2, 0));
			}
			break;
		case 11:
			render->SetTexture(GameEngine::eTexture::Shop_Closed);
			if (language <= 9) {
				render->SetTileIndex(sf::Vector2i(0, 0));
			}
			else if (language >= 10 && language <= 19) {
				render->SetTileIndex(sf::Vector2i(1, 0));
			}
			else {
				render->SetTileIndex(sf::Vector2i(2, 0));
			}
			break;
			break;
		case 12:
			render->SetTexture(GameEngine::eTexture::Shop_Work);
			break;
		}
	}
}

//close the current dialog box
void Game::GameBoard::HideDialog() {
	//if (inDialog) {
		std::cout << "HIDDEN_________________________________" << std::endl;
		try
		{
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_dialogBox);
			//inDialog = false;
			GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(m_dialogBox->AddComponent<GameEngine::SpriteRenderComponent>());
			render->SetTexture(GameEngine::eTexture::Blank);
		}
		catch (std::exception& e) {
			
		}
	//}
}

void Game::GameBoard::DrawBackground(int timeOfDay) {
	/*bg = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bg);

	bg->SetPos(sf::Vector2f(0, -42));
	bg->SetSize(sf::Vector2f(4000, 752));

	GameEngine::SpriteRenderComponent* renderBG = static_cast<GameEngine::SpriteRenderComponent*>(bg->AddComponent<GameEngine::SpriteRenderComponent>());

	renderBG->SetTopLeftRender(true);
	renderBG->SetFillColor(sf::Color::Transparent);*/


	if (timeOfDay == 0) {
		bg0 = new GameEngine::Entity();
		GameEngine::GameEngineMain::GetInstance()->AddEntity(bg0);

		bg0->SetPos(sf::Vector2f(0, -42));
		bg0->SetSize(sf::Vector2f(4000, 752));

		GameEngine::SpriteRenderComponent* renderBG = static_cast<GameEngine::SpriteRenderComponent*>(bg0->AddComponent<GameEngine::SpriteRenderComponent>());

		renderBG->SetTopLeftRender(true);
		renderBG->SetFillColor(sf::Color::Transparent);
		renderBG->SetZLevel(-3);
		renderBG->SetTexture(GameEngine::eTexture::Background_Day);
	}
	if (timeOfDay == 1) {
		bg1 = new GameEngine::Entity();
		GameEngine::GameEngineMain::GetInstance()->AddEntity(bg1);

		bg1->SetPos(sf::Vector2f(0, -42));
		bg1->SetSize(sf::Vector2f(4000, 752));

		GameEngine::SpriteRenderComponent* renderBG = static_cast<GameEngine::SpriteRenderComponent*>(bg1->AddComponent<GameEngine::SpriteRenderComponent>());

		renderBG->SetTopLeftRender(true);
		renderBG->SetFillColor(sf::Color::Transparent);
		renderBG->SetZLevel(-2);
		renderBG->SetTexture(GameEngine::eTexture::Background_Eve);
	}
	if (timeOfDay == 2) {
		bg2 = new GameEngine::Entity();
		GameEngine::GameEngineMain::GetInstance()->AddEntity(bg2);

		bg2->SetPos(sf::Vector2f(0, -42));
		bg2->SetSize(sf::Vector2f(4000, 752));

		GameEngine::SpriteRenderComponent* renderBG = static_cast<GameEngine::SpriteRenderComponent*>(bg2->AddComponent<GameEngine::SpriteRenderComponent>());

		renderBG->SetTopLeftRender(true);
		renderBG->SetFillColor(sf::Color::Transparent);
		renderBG->SetZLevel(-1);
		renderBG->SetTexture(GameEngine::eTexture::Background_Night);
	}

	/*switch (*timeOfDay) {
	case 0: renderBG->SetTexture(GameEngine::eTexture::Background_Day);
	case 1: renderBG->SetTexture(GameEngine::eTexture::Background_Eve);
	case 2: renderBG->SetTexture(GameEngine::eTexture::Background_Night);
	}*/
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
		language += 0;
		money += 50;
		break;
	case 3:
		language += 5;
		money += 20;
		break;
	}
}

void Game::GameBoard::NextDay() {
	/*for (int i = 0; i < GameEngine::GameEngineMain::GetInstance()->m_entities.size(); i++) {
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(GameEngine::GameEngineMain::GetInstance()->m_entities[i]);
	}*/
	//GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_player);
	GameEngine::GameEngineMain::GetInstance()->RemoveEntity(bg0);
	GameEngine::GameEngineMain::GetInstance()->RemoveEntity(bg1);
	GameEngine::GameEngineMain::GetInstance()->RemoveEntity(bg2);
	m_player->SetPos(sf::Vector2f(3800 / 2, 430.f));
	m_player->SetSize(sf::Vector2f(50.f, 100.f));
	language += 10;
	DrawGame(0, false);
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

void Game::GameBoard::leftAni() {
	GameEngine::AnimationComponent* m_animComponent = m_player->GetComponent<GameEngine::AnimationComponent>();
	m_animComponent->SetIsLooping(true);
	m_animComponent->PlayAnim(GameEngine::EAnimationId::Player_Left);
}

void Game::GameBoard::rightAni() {
	GameEngine::AnimationComponent* m_animComponent = m_player->GetComponent<GameEngine::AnimationComponent>();
	m_animComponent->SetIsLooping(true);
	m_animComponent->PlayAnim(GameEngine::EAnimationId::Player_Right);
}