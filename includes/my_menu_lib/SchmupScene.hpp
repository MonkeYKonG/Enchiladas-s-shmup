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

		virtual const SceneReturnValue Update(const sf::Vector2i & mousePos) throw (std::exception);
		virtual void Initialize(XMLNode::XMLNodePtr sceneRoot) throw (std::out_of_range, std::invalid_argument);
		virtual void Reset() throw(std::out_of_range, std::invalid_argument);

	protected:
		static const std::string SCENE_PLAYER_NODE;
		static const std::string SCENE_STAGES_NODE;
		static const std::string SCENE_ENEMIES_NODE;

		void InitializePlayer(XMLNode::XMLNodePtr playerNode) throw (std::out_of_range, std::invalid_argument);
		void InitializeEnemiesPoolStage(XMLNode::XMLNodePtr stagesNode) throw (std::out_of_range, std::invalid_argument);
		void InitializeEnemiesPoolEnemies(XMLNode::XMLNodePtr enemiesNode) throw (std::out_of_range, std::invalid_argument);
		virtual void UpdatePlayer() throw (std::exception);
		virtual void UpdateEnemiesPool() throw (std::out_of_range, std::invalid_argument);
		virtual void UpdateEnemies() throw (std::exception);
		virtual void UpdateShoots() throw (std::exception);
		virtual void UpdateColisions() throw (std::exception);
		virtual void UpdateObjects() throw (std::exception);

		virtual const EnemiesPool::EnemiesList GeneratingEnemiesList() throw (std::out_of_range, std::invalid_argument);
		virtual void AddingNewEnemies(const EnemiesPool::EnemiesList & newEnemies) noexcept;
		virtual void AddingNewEnemy(Enemy::EnemyPtr newEnemy) noexcept;

		virtual void UpdatingPlayer() throw (std::exception);
		virtual void TriggerPlayerShooting() throw (std::out_of_range, std::invalid_argument);
		virtual const Shooter::ShootList GeneratingPlayerBullets() throw (std::out_of_range, std::invalid_argument);
		virtual void AddingNewPlayerBullets(Shooter::ShootList & newBullets) noexcept;
		virtual void PreparingPlayerBuller(Bullet::BulletPtr newBullet) noexcept;
		virtual void AddingPlayerBullet(Bullet::BulletPtr newBullet) noexcept;

		virtual void UpdatingEnemy(EnemiesPool::EnemiesList::iterator & enemyIt) throw (std::exception);
		virtual void TriggerRemoveEnemy(EnemiesPool::EnemiesList::iterator & enemyIt) noexcept;

		virtual void UpdatingPlayerBullet(Shooter::ShootList::iterator & bulletIt) throw (std::exception);
		virtual void TriggerRemovePlayerBullet(Shooter::ShootList::iterator & bulletIt) noexcept;
		virtual void UpdatingEnemiesBullet(Shooter::ShootList::iterator & bulletIt) throw (std::exception);
		virtual void TriggerRemoveEnemiesBullet(Shooter::ShootList::iterator & bulletIt) noexcept;

		virtual void TriggerEnemyIsDamaged(Shooter::ShootList::iterator & bulletIt, EnemiesPool::EnemiesList::iterator &enemyIt) noexcept;
		virtual void TriggerPlayerIsDamaged(Shooter::ShootList::iterator & bulletIt) noexcept;

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

		EnemiesPool	m_enemiesPool;
		Player::PlayerPtr m_player;
		EnemiesPool::EnemiesList m_enemies;
		Shooter::ShootList m_playerShoots;
		Shooter::ShootList m_enemiesShoots;
	};
}