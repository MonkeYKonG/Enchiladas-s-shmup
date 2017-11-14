#pragma once

#include "MainMenu.hpp"
#include "my_objects_lib/Player.hpp"

namespace my
{
	class SchmupScene : public MainMenu
	{
	public:
		SchmupScene();
		virtual ~SchmupScene() {}

		virtual const SceneReturnValue Update(sf::RenderWindow & window) throw (std::exception);
		virtual void Initialize(XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range, std::invalid_argument);
		virtual void Reset() throw(std::out_of_range, std::invalid_argument);

	protected:
		static const std::string SCENE_PLAYER_NODE;

		void InitializePlayer(XMLNode::XMLNodePtr playerNode) throw (std::out_of_range, std::invalid_argument);

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

		Player::PlayerPtr m_player;
	};
}