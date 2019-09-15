#include "TextRenderComponent.h"

#include "GameEngine\GameEngineMain.h"

using namespace GameEngine;

TextRenderComponent::TextRenderComponent()
{

}

TextRenderComponent::~TextRenderComponent()
{

}

void TextRenderComponent::OnAddToWorld()
{
	__super::OnAddToWorld();
	UpdateSpriteParams();
}

void TextRenderComponent::UpdateSpriteParams()
{
	// Todo support non top-left render
	m_text.setOrigin(sf::Vector2f(0, 0));
}

void TextRenderComponent::Render(sf::RenderTarget* target)
{
	__super::Render(target);

	if (!target)
	{
		return;
	}

	m_text.setPosition(GetEntity()->GetPos());
	m_text.setRotation(GetEntity()->GetRot());
	m_text.setCharacterSize(50);

	target->draw(m_text);
}