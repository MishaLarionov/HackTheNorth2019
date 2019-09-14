#include "PlayerMovementComponent.h"
#include "GameEngine\GameEngineMain.h"

#include <SFML/Window/Keyboard.hpp>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
{

}

PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::GetDialog(int x)
{
	
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

	sf::Vector2f playerVelocity = sf::Vector2f(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		playerVelocity.x -= playerSpeed * delta;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerVelocity.x += playerSpeed * delta;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) 
	{
		// Player wants to interact with the nearest NPC
		GetDialog(playerVelocity.x);
	}

	// Update entity with pos values
	GetEntity()->SetPos(GetEntity()->GetPos() + playerVelocity);
}