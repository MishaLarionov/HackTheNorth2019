#pragma once
#include "GameEngine\EntitySystem\Entity.h"

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>

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
		std::vector<int> GetNPCsX() { return m_npcsx; }

		static std::string m_houses[];
		
		int* language;
		int* money;

		int* m_timeOfDay;

	private:
		void DrawGame(int time);
		void DrawBackground(int time);
		void CreatePlayer();
		void CreateNPC();
		void NewHouse(float hpos);
		void NewStore(float hPos);
		void ShowDialog(int id);
		void HideDialog();
		void UpdateValues(int caseNum);

		std::vector<int> m_npcsx;

	};
}
