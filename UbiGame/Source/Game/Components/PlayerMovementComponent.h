#pragma once
#include "GameEngine\EntitySystem\Component.h"

namespace Game
{
	class PlayerMovementComponent : public GameEngine::Component
	{
	public:
		PlayerMovementComponent();
		~PlayerMovementComponent();

		void GetDialog();

		virtual void Update() override;
		virtual void OnAddToWorld() override;
	};
}