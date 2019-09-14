#pragma once
#include "GameEngine\EntitySystem\Entity.h"

#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Game
{
	//Used for storing and controlling all game related entities, as well as providing an entry point for the "game" side of application
	class PlayerEntity;

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();

		void Update();
		bool IsGameOver() { return false; }

		GameEngine::Entity* m_player;
		GameEngine::Entity* m_dialogBox;
		std::vector<GameEngine::Entity*> m_npcs;
		std::vector<int> m_npcsx;

		int* language;
		int* money;

	private:
		void CreatePlayer();
		void CreateNPC();
		void NewHouse(float hpos);
		void NewStore(float hPos);
		void ShowDialog(int id);
		void HideDialog();
		void UpdateValues(int caseNum);
	};
}
