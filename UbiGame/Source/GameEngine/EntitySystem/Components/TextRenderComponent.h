#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "GameEngine\EntitySystem\Components\RenderComponent.h"

namespace GameEngine
{
	class TextRenderComponent : public RenderComponent
	{
	public:
		TextRenderComponent();
		virtual ~TextRenderComponent();

		// virtual void Update() override;

		virtual void Render(sf::RenderTarget* target) override;
		virtual void OnAddToWorld() override;

		virtual void SetText(sf::String text) { m_text.setString(static_cast<sf::String>(text)); };

	private:
		sf::Text m_text;

		void UpdateSpriteParams();

	};
}
