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

		void Update() noexcept;
		const EnemiesList GetEnemies() throw (std::out_of_range, std::invalid_argument);

	private:
		struct EnemiesWave
		{
			bool needCleaning = false;
			unsigned timeToBegin = 0;
			EnemiesNodeList enemiesList;
		};

		typedef std::vector<EnemiesWave> WavesList;

		XMLNode::XMLNodePtr m_enemiesNode;
		WavesList m_waves;
	};
}