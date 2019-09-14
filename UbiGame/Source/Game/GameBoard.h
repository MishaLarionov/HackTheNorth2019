#pragma once
#include "GameEngine\EntitySystem\Entity.h"

#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Game
{
	//Used for storing and controling all game related entities, as well as providing an entry point for the "game" side of application	
	class PlayerEntity;	

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();

		void Update();		
		bool IsGameOver() { return false; }
		GameEngine::Entity* m_player;
		GameEngine::Entity* dialogueBox;

		float gameTime;

		void CreatePlayer();
		void NewHouse(float hpos);
		void ShowDialogue(int id);
		void HideDialogue();

	private:

	};
}

