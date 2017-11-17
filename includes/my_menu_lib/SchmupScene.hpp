#pragma once

#include "MainMenu.hpp"
#include "my_objects_lib/Player.hpp"
#include "my_objects_lib/EnemiesPool.hpp"

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
		static const std::string SCENE_STAGES_NODE;
		static const std::string SCENE_ENEMIES_NODE;

		void InitializePlayer(XMLNode::XMLNodePtr playerNode) throw (std::out_of_range, std::invalid_argument);
		void InitializeEnemiesPoolStage(XMLNode::XMLNodePtr stagesNode) throw (std::out_of_range, std::invalid_argument);
		void InitializeEnemiesPoolEnemies(XMLNode::XMLNodePtr enemiesNode) throw (std::out_of_range, std::invalid_argument);
		void UpdatePlayer() throw (std::out_of_range);
		void UpdateShoots() throw (std::out_of_range);
		void UpdateObjects() throw (std::out_of_range);

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

		EnemiesPool	m_enemiesPool;
		Player::PlayerPtr m_player;
		Shooter::ShootList m_playerShoots;
		Shooter::ShootList m_enemiesShoots;
	};
}