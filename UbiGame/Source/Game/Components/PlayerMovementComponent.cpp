#include "PlayerMovementComponent.h"
#include "GameEngine\GameEngineMain.h"

#include <Game/GameBoard.h>

#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <vector>
#include <GameEngine\EntitySystem\Components\SpriteRenderComponent.h>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
{

}

PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::GetDialog(int x)
{

	std::vector<int> npcsx = GameEngine::GameEngineMain::GetInstance()->GetGameBoardObject()->GetNPCsX();

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
	std::cout << GameEngine::GameEngineMain::m_gameTime << std::endl;

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
		GetDialog(playerVelocity.x);
	}

	// Update entity with pos values
	if (GetEntity()->GetPos().x + playerVelocity.x < 3800 && GetEntity()->GetPos().x + playerVelocity.x > 0) {
		GetEntity()->SetPos(GetEntity()->GetPos() + playerVelocity);
	}
}