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

void PlayerMovementComponent::GetDialog()
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
		Game::GameBoard::gameTime += 0.1 * delta;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		playerVelocity.x += playerSpeed * delta;
		Game::GameBoard::gameTime += 0.1 * delta;
	}

	// Update entity with pos values
	GetEntity()->SetPos(GetEntity()->GetPos() + playerVelocity);
}