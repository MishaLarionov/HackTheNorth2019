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
		void ShowDialog(int id);
		void HideDialog();
		bool IsGameOver() { return false; }

		GameEngine::Entity* m_player;
		GameEngine::Entity* m_dialogBox;
		GameEngine::Entity getPlayer () { m_player; }

		std::vector<GameEngine::Entity*> m_npcs;
		std::vector<int> GetNPCsX() { return m_npcsx; }

		int* language;
		int* money;

	private:
		void DrawBackground();
		void CreatePlayer();
		void CreateNPC();
		void NewHouse(float hpos);
		void NewStore(float hPos);
		void UpdateValues(int caseNum);

		std::vector<int> m_npcsx;

	};
}
