#pragma once

#include "Enemy.hpp"
#include "my_graph_lib/XMLNode.hpp"

namespace my
{
	class EnemiesPool
	{
	public:
		typedef std::vector<Enemy::EnemyPtr> EnemiesList;
		typedef std::vector<XMLNode::XMLNodePtr> EnemiesNodeList;

		EnemiesPool();
		~EnemiesPool();

		void InitializeStage(XMLNode::XMLNodePtr stageNode) throw (std::out_of_range, std::invalid_argument);
		void InitializeEnemies(XMLNode::XMLNodePtr enemiesNode) throw (std::out_of_range, std::invalid_argument);

		const EnemiesList Update(bool isClean) throw (std::out_of_range, std::invalid_argument);
		bool IsWavesClear() const noexcept;

	private:
		struct EnemiesWave
		{
			typedef std::pair<XMLNode::XMLNodePtr, sf::Vector2f> WaveEnemy;
			typedef std::vector<WaveEnemy> WaveEnemiesList;

			bool needCleaning = false;
			unsigned timeToBegin = 0;
			WaveEnemiesList enemiesList;
		};

		typedef std::vector<EnemiesWave> WavesList;

		XMLNode::XMLNodePtr m_enemiesNode;
		WavesList m_waves;
		unsigned m_curWave;
		unsigned m_waveFramerate;
	};
}