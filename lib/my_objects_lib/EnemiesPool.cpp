#include "EnemiesPool.hpp"
#include "ObjectPool.hpp"

my::EnemiesPool::EnemiesPool()
{}

my::EnemiesPool::~EnemiesPool()
{}

void my::EnemiesPool::InitializeStage(XMLNode::XMLNodePtr stageNode) throw (std::out_of_range, std::invalid_argument)
{
	if (!stageNode)
		throw (std::invalid_argument("EnemiesPool: InitializeStage: null node"));
	try
	{
		for (unsigned i = 0; i < stageNode->GetChilds().size(); ++i)
		{
			m_waves.push_back(EnemiesWave());
			if (stageNode->GetChilds()[i]->ContentExist("needClean"))
			{
				if (stageNode->GetChilds()[i]->GetContent("needClean").second == "true")
					m_waves.back().needCleaning = true;
				else if (stageNode->GetChilds()[i]->GetContent("needClean").second == "false")
					m_waves.back().needCleaning = false;
				else
					throw (std::invalid_argument("EnemiesPool: InitializeStage: invalid node content needClean=\"" + stageNode->GetChilds()[i]->GetContent("needClean").second + "\""));
			}
			if (stageNode->GetChilds()[i]->ContentExist("timeToBegin"))
				m_waves.back().timeToBegin = std::stoul(stageNode->GetChilds()[i]->GetContent("timeToBegin").second);
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

void my::EnemiesPool::Update() noexcept
{

}

const my::EnemiesPool::EnemiesList my::EnemiesPool::GetEnemies() throw (std::out_of_range, std::invalid_argument)
{
	return (EnemiesList());
}