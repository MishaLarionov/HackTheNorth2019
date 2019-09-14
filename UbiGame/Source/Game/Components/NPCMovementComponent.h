#pragma once
#include "GameEngine\EntitySystem\Component.h"

namespace Game 
{

	class NPCMovementComponent : public GameEngine::Component
	{
	public:
		NPCMovementComponent(float x);
		~NPCMovementComponent();

		int* x;

		virtual void Update() override;
		virtual void OnAddToWorld() override;
	};

}