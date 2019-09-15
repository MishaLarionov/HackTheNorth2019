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
		void ShowDialog(int id);
		void HideDialog();
		bool IsGameOver() { return false; }

		GameEngine::Entity* m_player;
		GameEngine::Entity* m_dialogBox;
		GameEngine::Entity getPlayer () { m_player; }

		std::vector<GameEngine::Entity*> m_npcs;
		std::vector<int> GetNPCsX() { return m_npcsx; }

		static std::string m_houses[];

		bool inDialog;

		int* language;
		int* money;
		int* m_timeOfDay;

	private:
		void DrawGame(int time);
		void DrawBackground(int time);
		void CreatePlayer();
		void CreateNPC(int x);
		void NewHouse(float hpos);
		void NewStore(float hPos);
		void UpdateValues(int caseNum);

		std::vector<int> m_npcsx;

	};
}
