#include "AnimationManager.h"


using namespace GameEngine;

AnimationManager* AnimationManager::sm_instance = nullptr;

AnimationManager::AnimationManager()
{

}


AnimationManager::~AnimationManager()
{

}


void AnimationManager::InitStaticGameAnimations()
{
	/*
	//Template definition -> every new animation needs to have an ID and a definition that controls how animation is played
	m_animDefinitions.push_back
	(
	SAnimationDefinition(
	EAnimationId::BirdIdle,
	eTexture::Player,
	sf::Vector2i(0, 0),
	10,
	3)
	);
	*/
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::Player_Left,
			eTexture::Player_Left,
			sf::Vector2i(0, 0),
			2,
			5)
	);
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::Player_Right,
			eTexture::Player_Right,
			sf::Vector2i(0, 0),
			2,
			5)
	);
}


void AnimationManager::ReleaseStaticGameAnimations()
{
	m_animDefinitions.clear();
}


const SAnimationDefinition* AnimationManager::GetAnimDefinition(EAnimationId::type animId) const
{
	for (int a = 0; a < m_animDefinitions.size(); ++a)
	{
		if (m_animDefinitions[a].m_animId == animId)
			return &m_animDefinitions[a];
	}

	return nullptr;
}
