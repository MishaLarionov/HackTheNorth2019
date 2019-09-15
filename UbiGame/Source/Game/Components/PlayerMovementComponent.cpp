#include "PlayerMovementComponent.h"
#include "GameEngine\GameEngineMain.h"
#include <GameEngine\EntitySystem\Components\SpriteRenderComponent.h>

#include <Game/GameBoard.h>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
{

}

PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::GetDialog(int x)
{

	std::cout << "SHOW DIALOG FUNCTION CALLED" << std::endl;
	// This function is used to keep track/select which npc to interact with
	std::vector<int> npcsx = GameEngine::GameEngineMain::GetInstance()->GetGameBoardObject()->GetNPCsX();

	int min = INT_MAX;

	for (auto nx : npcsx) {
		int abx = std::abs(x-nx);
		if (abx <= 80 && abx < min) {
			min = nx;
		}
		std::cout << "PLAYER: " << x << std::endl;
		std::cout << "POSITION: " << nx << std::endl;
		std::cout << "DISTANCE: " << abx << std::endl;
	}

	if (min == INT_MAX) {
		//
		std::cout << "TOO FAR! COME CLOSER!" << std::endl;
	}
	else {
		std::cout << "NPC INTERACTED!" << std::endl;
		// NPC Found
		GameEngine::GameEngineMain::GetInstance()->GetGameBoardObject()->ShowDialog(10);
	}

}

void PlayerMovementComponent::OnAddToWorld()
{
	__super::OnAddToWorld();

}

void PlayerMovementComponent::Update()
{
	__super::Update();

	float delta = GameEngine::GameEngineMain::GetTimeDelta();

	float playerSpeed = 200.f;
	float timeScale = 0.08f;

	sf::Vector2f playerVelocity = sf::Vector2f(0.f, 0.f);
	//float* gameT = Game::GameBoard::gameTime;
	// std::cout << GameEngine::GameEngineMain::m_gameTime << std::endl;

	GameEngine::SpriteRenderComponent* playerSprite = GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>() ;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		playerVelocity.x -= playerSpeed * delta;
		GameEngine::GameEngineMain::m_gameTime += timeScale * delta;
		playerSprite->SetTexture(GameEngine::eTexture::Player_Left);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		playerVelocity.x += playerSpeed * delta;
		GameEngine::GameEngineMain::m_gameTime += timeScale * delta;
		playerSprite->SetTexture(GameEngine::eTexture::Player_Right);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		// Player wants to interact with the nearest NPC
		GetDialog(GetEntity()->GetPos().x);
	}

	// Update entity with pos values
	if (GetEntity()->GetPos().x + playerVelocity.x < 3800 && GetEntity()->GetPos().x + playerVelocity.x > 0) {
		GetEntity()->SetPos(GetEntity()->GetPos() + playerVelocity);
	}
}
