#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
	//TODO - if needed, move out of Engine part to some sort of loader on the game side of things
	namespace eTexture
	{
		enum type
		{
			None = -1, // THIS ONE HAS TO BE FIRST
			SampleHouse,
			BottomTiles,
			Doors,
			Windows,
			RoofTiles,
			Store,
			Background_Day,
			Background_Eve,
			Background_Night,
			Interact_Hint,
			Player_Left,
			Player_Right,
			Npc_Left,
			Npc_Right,
			Shop_Work,
			Count, // THIS ONE HAS TO BE LAST
		};
	}

	inline const char* GetPath(eTexture::type texture)
	{
		// TODO: add image and resource file paths
		switch (texture) {
			case eTexture::SampleHouse: return "SampleHouse.png";
			case eTexture::BottomTiles: return "BottomTiles.png";
			case eTexture::Doors: return "Doors.png";
			case eTexture::Windows: return "Windows.png";
			case eTexture::RoofTiles: return "RoofTiles.png";
			case eTexture::Store: return "Store.png";
			case eTexture::Background_Day: return "background4000.png";
			case eTexture::Background_Eve: return "background4000-eve.png";
			case eTexture::Background_Night: return "background4000-night.png";
			case eTexture::Interact_Hint: return "Interact_Hint.png";
			case eTexture::Player_Left: return "WalkLeft.png";
			case eTexture::Player_Right: return "WalkRight.png";
			case eTexture::Npc_Left: return "NpcLeft.png";
			case eTexture::Npc_Right: return "NpcRight.png";
			case eTexture::Shop_Work: return "ShopDialog.png";
		}

		return "UnknownTexType";
	}

	class TextureManager
	{
	public:
		static TextureManager* GetInstance() { if (!sm_instance) sm_instance = new TextureManager(); return sm_instance; }
		~TextureManager();

		void LoadTextures();
		void UnLoadTextures();

		sf::Texture* GetTexture(eTexture::type texture) const { return m_textures[(int)texture]; }

	private:
		TextureManager();
		static TextureManager* sm_instance;

		sf::Texture* m_textures[eTexture::Count];
	};
}

namespace TextureHelper
{
	static sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture)
	{
		switch (texture)
		{
			case GameEngine::eTexture::BottomTiles: return sf::Vector2f(200.f, 400.f);
			case GameEngine::eTexture::Doors: return sf::Vector2f(70.f, 110.f);
			case GameEngine::eTexture::Windows: return sf::Vector2f(60.f, 70.f);
			case GameEngine::eTexture::RoofTiles: return sf::Vector2f(200.f, 43.f);
			case GameEngine::eTexture::Player_Left: return sf::Vector2f(50.f, 100.f);
			case GameEngine::eTexture::Player_Right: return sf::Vector2f(50.f, 100.f);
			case GameEngine::eTexture::Npc_Left: return sf::Vector2f(50.f, 100.f);
			case GameEngine::eTexture::Npc_Right: return sf::Vector2f(50.f, 100.f);
			case GameEngine::eTexture::Shop_Work: return sf::Vector2f(600.f, 300.f);
		}
		return sf::Vector2f(-1.f, -1.f);
	}
}
