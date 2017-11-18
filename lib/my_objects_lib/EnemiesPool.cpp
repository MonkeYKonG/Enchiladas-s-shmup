#include "EnemiesPool.hpp"
#include "ObjectPool.hpp"

#include <iostream>

my::EnemiesPool::EnemiesPool()
	: m_curWave(0)
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
				std::cout << childStk->GetChilds()[j]->GetName() << std::endl;
				std::cout << std::stol(childStk->GetChilds()[j]->GetContent("x").second) << std::endl;
				std::cout << std::stol(childStk->GetChilds()[j]->GetContent("y").second) << std::endl;
				m_waves.back().enemiesList.push_back(
					EnemiesWave::WaveEnemy(
						m_enemiesNode->GetChild(
							childStk->GetChilds()[j]->GetName()
						), 
						sf::Vector2f(
							std::stof(
								childStk->GetChilds()[j]->GetContent("x").second
							), 
							std::stof(
								childStk->GetChilds()[j]->GetContent("y").second
							)
						)
					)
				);
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

void my::EnemiesPool::Update(bool isClean) noexcept
{

}

const my::EnemiesPool::EnemiesList my::EnemiesPool::GetEnemies() throw (std::out_of_range, std::invalid_argument)
{
	return (EnemiesList());
}