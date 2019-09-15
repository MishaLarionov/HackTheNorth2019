#pragma once
#include "GameEngine\EntitySystem\Component.h"

namespace Game
{
	class PlayerMovementComponent : public GameEngine::Component
	{
	public:
		PlayerMovementComponent();
		~PlayerMovementComponent();

		void GetDialog(int x);
		bool dialogDisplay;

		virtual void Update() override;
		virtual void OnAddToWorld() override;
	};
}