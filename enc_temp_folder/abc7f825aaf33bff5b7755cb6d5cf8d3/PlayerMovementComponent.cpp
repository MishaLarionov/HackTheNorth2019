#include "PlayerMovementComponent.h"
#include "GameEngine\GameEngineMain.h"
#include <GameEngine\Util\AnimationManager.h>
#include <GameEngine\EntitySystem\Components\SpriteRenderComponent.h>
#include <GameEngine\EntitySystem\Components\AnimationComponent.h>

#include <Game/GameBoard.h>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
{
	dialogDisplay = false;
	dir = 0;
}

PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::GetDialog(int x)
{

	// Special escape cases
	if (x == -101) {
		GameEngine::GameEngineMain::GetInstance()->GetGameBoardObject()->ShowDialog(101);
	}
	else if (x == -102) {
		GameEngine::GameEngineMain::GetInstance()->GetGameBoardObject()->ShowDialog(102);
	}
	else {

		std::cout << "SHOW DIALOG FUNCTION CALLED" << std::endl;
		// This function is used to keep track/select which npc to interact with
		std::vector<int> npcsx = GameEngine::GameEngineMain::GetInstance()->GetGameBoardObject()->GetNPCsX();

		int min = INT_MAX;

		for (auto nx : npcsx) {
			int abx = std::abs(x - nx);
			if (abx <= 80 && abx < min) {
				min = nx;
			}
			//std::cout << "PLAYER: " << x << std::endl;
			//std::cout << "POSITION: " << nx << std::endl;
			//std::cout << "DISTANCE: " << abx << std::endl;
		}

		if (min == INT_MAX) {
			//
			dialogDisplay = false;
			std::cout << "TOO FAR! COME CLOSER!" << std::endl;
			//GameEngine::GameEngineMain::GetInstance()->GetGameBoardObject()->HideDialog();
		}
		else {
			std::cout << "NPC INTERACTED!" << std::endl;
			// NPC Found
			GameEngine::GameEngineMain::GetInstance()->GetGameBoardObject()->ShowDialog(10);
		}
	}

}

void PlayerMovementComponent::OnAddToWorld()
{
	__super::OnAddToWorld();

}

void PlayerMovementComponent::Update()
{
	__super::Update();

	GameEngine::SpriteRenderComponent* playerSprite = GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>();
		
	m_animComponent = GetEntity()->GetComponent<GameEngine::AnimationComponent>();
	m_animComponent->SetIsLooping(true);
	m_animComponent->PlayAnim(GameEngine::EAnimationId::Player_Left);

	float delta = GameEngine::GameEngineMain::GetTimeDelta();

	float playerSpeed = 200.f;
	float timeScale = 0.08f;

	sf::Vector2f playerVelocity = sf::Vector2f(0.f, 0.f);
	//std::cout << GameEngine::GameEngineMain::m_gameTime << std::endl;

	//std::cout << "DISPLAY BOOLEAN:" << dialogDisplay << std::endl;

	if (!dialogDisplay) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			dir = -1;
			playerVelocity.x -= playerSpeed * delta;
			GameEngine::GameEngineMain::m_gameTime += timeScale * delta;
			playerSprite->SetTexture(GameEngine::eTexture::Player_Left);
			m_animComponent->PlayAnim(GameEngine::EAnimationId::Player_Left);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			dir = 1;
			playerVelocity.x += playerSpeed * delta;
			GameEngine::GameEngineMain::m_gameTime += timeScale * delta;
			playerSprite->SetTexture(GameEngine::eTexture::Player_Right);
			m_animComponent->PlayAnim(GameEngine::EAnimationId::Player_Right);
		}

		// Update entity with pos values
		if (GetEntity()->GetPos().x + playerVelocity.x < 3800 && GetEntity()->GetPos().x + playerVelocity.x > 0) {
			GetEntity()->SetPos(GetEntity()->GetPos() + playerVelocity);
		}

		if (!dialogDisplay && sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			dialogDisplay = true;
			// Player wants to interact with the nearest NPC
			GetDialog(GetEntity()->GetPos().x);
		}

	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && dialogDisplay) {
			dialogDisplay = false;
			GameEngine::GameEngineMain::GetInstance()->GetGameBoardObject()->HideDialog();
			GetDialog(101);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && dialogDisplay) {
			dialogDisplay = false;
			GameEngine::GameEngineMain::GetInstance()->GetGameBoardObject()->HideDialog();
			GetDialog(102);
		}
	}

}
