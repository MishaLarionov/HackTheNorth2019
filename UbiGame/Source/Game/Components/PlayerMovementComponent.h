#pragma once
#include "GameEngine\EntitySystem\Component.h"
#include <GameEngine\EntitySystem\Components\AnimationComponent.h>

namespace Game
{
	class PlayerMovementComponent : public GameEngine::Component
	{
	public:
		PlayerMovementComponent();
		~PlayerMovementComponent();

		void GetDialog(int x);

		// -1 is left, 1 is right, 0 is still
		int dir;
		GameEngine::AnimationComponent* m_animComponent;
		bool dialogDisplay;

		virtual void Update() override;
		virtual void OnAddToWorld() override;
	};
}