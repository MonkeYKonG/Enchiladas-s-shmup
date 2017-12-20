#include "EnemiesPool.hpp"
#include "ObjectPool.hpp"

#include <iostream>

my::EnemiesPool::EnemiesPool()
	: m_curWave(0), m_waveFramerate(0)
{}

my::EnemiesPool::~EnemiesPool()
{}

void my::EnemiesPool::InitializeStage(XMLNode::XMLNodePtr stageNode) throw (std::out_of_range, std::invalid_argument)
{
	XMLNode::XMLNodePtr childStk;
	if (!stageNode)
		throw (std::invalid_argument("EnemiesPool: InitializeStage: null node"));
	try
	{
		for (unsigned i = 0; i < stageNode->GetChilds().size(); ++i)
		{
			m_waves.push_back(EnemiesWave());
			childStk = stageNode->GetChilds()[i];
			std::cout << childStk->GetName() << std::endl;
			if (childStk->ContentExist("needClean"))
			{
				if (childStk->GetContent("needClean").second == "true")
					m_waves.back().needCleaning = true;
				else if (childStk->GetContent("needClean").second == "false")
					m_waves.back().needCleaning = false;
				else
					throw (std::invalid_argument("EnemiesPool: InitializeStage: invalid node content needClean=\"" + stageNode->GetChilds()[i]->GetContent("needClean").second + "\""));
			}
			if (childStk->ContentExist("timeToBegin"))
				m_waves.back().timeToBegin = std::stoul(childStk->GetContent("timeToBegin").second);
			for (unsigned j = 0; j < childStk->GetChilds().size(); ++j)
			{
				m_waves.back().enemiesList.push_back(EnemiesWave::WaveEnemy(m_enemiesNode->GetChild(childStk->GetChilds()[j]->GetName()), sf::Vector2f(std::stof(childStk->GetChilds()[j]->GetContent("x").second), std::stof(childStk->GetChilds()[j]->GetContent("y").second))));
			}
		}
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
	catch (const std::invalid_argument & e)
	{
		throw (e);
	}
}

void my::EnemiesPool::InitializeEnemies(XMLNode::XMLNodePtr enemiesNode) throw (std::out_of_range, std::invalid_argument)
{
	if (!enemiesNode)
		throw (std::invalid_argument("EnemiesPool: InitializeEnemies: null node"));
	if (enemiesNode->GetChilds().empty())
		throw (std::invalid_argument("EnemiesPool: InitializeEnemies: empty node"));
	try
	{
		m_enemiesNode = enemiesNode;
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
	catch (const std::invalid_argument & e)
	{
		throw (e);
	}
}

const my::EnemiesPool::EnemiesList my::EnemiesPool::Update(bool isClean) throw (std::out_of_range, std::invalid_argument)
{
	EnemiesList enemiesList;
	Enemy::EnemyPtr newEnemy;

	try
	{
		if (IsWavesClear())
			return (enemiesList);
		if ((m_waves[m_curWave].needCleaning && isClean) || !m_waves[m_curWave].needCleaning)
		{
			if (m_waveFramerate < m_waves[m_curWave].timeToBegin)
				m_waveFramerate++;
			else
			{
				m_waveFramerate = 0;
				for (unsigned i = 0; i < m_waves[m_curWave].enemiesList.size(); ++i)
				{
					newEnemy = ObjectPool::CreateEnemy(m_waves[m_curWave].enemiesList[i].first);
					newEnemy->setPosition(m_waves[m_curWave].enemiesList[i].second);
					enemiesList.push_back(newEnemy);
				}
				m_curWave++;
			}
		}
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
	catch (const std::invalid_argument & e)
	{
		throw (e);
	}
	return (enemiesList);
}

bool my::EnemiesPool::IsWavesClear() const noexcept
{
	return (m_curWave >= m_waves.size());
}