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
			None = -1,
			Count,
			Player,
			Player_walk_left,
			Player_walk_right,
			Building1,
			StoreDialog_1,
			StoreDialog_2,
			StoreDialog_3,
			Character1,
			Character1Dialog,
		};
	}	

	inline const char* GetPath(eTexture::type texture)
	{
		// TODO: add image and resource file paths
		switch (texture) {
			case eTexture::Player: return ".png";
			case eTexture::Player_walk_left: return ".png";
			case eTexture::Player_walk_right: return ".png";
			case eTexture::Building1: return ".png";
			case eTexture::StoreDialog_3: return "Assets/dialog/StoreDialog_3.png";
			case eTexture::Character1: return ".png";
			case eTexture::Character1Dialog: return ".png";
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
		return sf::Vector2f(-1.f, -1.f);
	}
}

