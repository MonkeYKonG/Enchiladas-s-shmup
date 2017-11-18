#include "SchmupScene.hpp"
#include "my_objects_lib/ObjectPool.hpp"

const std::string my::SchmupScene::SCENE_PLAYER_NODE = "player";
const std::string my::SchmupScene::SCENE_STAGES_NODE = "stages";
const std::string my::SchmupScene::SCENE_ENEMIES_NODE = "enemies";

my::SchmupScene::SchmupScene()
{}

const my::SceneReturnValue my::SchmupScene::Update(sf::RenderWindow & window) throw(std::exception)
{
	SceneReturnValue returnValue;

	try
	{
		returnValue = MainMenu::Update(window);
		if (returnValue.value == STATE_RETURN::CLOSE)
			return (returnValue);
		UpdateObjects();
	}
	catch (const std::exception & e)
	{
		throw (e);
	}
	return (returnValue);
}

void my::SchmupScene::Initialize(XMLNode::XMLNodePtr sceneRoot) throw(std::out_of_range, std::invalid_argument)
{
	try
	{
		m_initializationFunctions.push_back(MainMenu::InitFunctionPair(SCENE_PLAYER_NODE, static_cast<InitializationFunction>(&SchmupScene::InitializePlayer)));
		m_initializationFunctions.push_back(MainMenu::InitFunctionPair(SCENE_STAGES_NODE, static_cast<InitializationFunction>(&SchmupScene::InitializeEnemiesPoolStage)));
		m_initializationFunctions.push_back(MainMenu::InitFunctionPair(SCENE_ENEMIES_NODE, static_cast<InitializationFunction>(&SchmupScene::InitializeEnemiesPoolEnemies)));
		MainMenu::Initialize(sceneRoot);
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

void my::SchmupScene::Reset() throw(std::out_of_range, std::invalid_argument)
{
	try
	{
		MainMenu::Reset();
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

void	my::SchmupScene::InitializePlayer(XMLNode::XMLNodePtr playerNode) throw (std::out_of_range, std::invalid_argument)
{
	try
	{
		if (!(m_player = ObjectPool::CreatePlayer(playerNode)))
			throw (std::invalid_argument("SchmupScene: InitializePlayer: can't create player"));
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

void	my::SchmupScene::InitializeEnemiesPoolStage(XMLNode::XMLNodePtr stagesNode) throw (std::out_of_range, std::invalid_argument)
{
	if (!stagesNode)
		throw (std::invalid_argument("SchmupScene: InitializeEnemiesPool: null stages node"));
	try
	{
		m_enemiesPool.InitializeStage(stagesNode->GetChilds()[0]);
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

void	my::SchmupScene::InitializeEnemiesPoolEnemies(XMLNode::XMLNodePtr enemiesNode) throw (std::out_of_range, std::invalid_argument)
{

	if (!enemiesNode)
		throw (std::invalid_argument("SchmupScene: InitializeEnemiesPool: null enemies node"));
	try
	{
		m_enemiesPool.InitializeEnemies(enemiesNode);
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

void	my::SchmupScene::UpdateEnemiesPool() throw (std::out_of_range)
{
	EnemiesPool::EnemiesList newEnemies;

	try
	{
		newEnemies = m_enemiesPool.Update(m_enemies.empty());
		for (unsigned i = 0; i < newEnemies.size(); ++i)
			m_enemies.push_back(newEnemies[i]);
	}
	catch (const std::invalid_argument & e)
	{
		throw (e);
	}
}

void	my::SchmupScene::UpdatePlayer() throw (std::out_of_range)
{
	Shooter::ShootList newShoots;

	try
	{
		if (m_player)
		{
			m_player->Update();
			if (m_player->CanShoot())
			{
				newShoots = m_player->GetShootList();
				for (unsigned i = 0; i < newShoots.size(); ++i)
				{
					newShoots[i]->setPosition(m_player->getPosition());
					m_playerShoots.push_back(newShoots[i]);
				}
				m_player->SetCanShoot(false);
			}
		}
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

void	my::SchmupScene::UpdateEnemies() throw (std::out_of_range)
{
	EnemiesPool::EnemiesList::iterator it;
	try
	{
		it = m_enemies.begin();
		while (it != m_enemies.end())
		{
			(*it)->Update();
			if ((*it)->IsFinish())
				it = m_enemies.erase(it);
			else
				it++;
		}
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

void	my::SchmupScene::UpdateShoots() throw (std::out_of_range)
{
	Shooter::ShootList::iterator it;

	try
	{
		it = m_playerShoots.begin();
		while (it != m_playerShoots.end())
		{
			(*it)->Update();
			if ((*it)->IsFinish())
				it = m_playerShoots.erase(it);
			else
				it++;
		}
		it = m_enemiesShoots.begin();
		while (it != m_enemiesShoots.end())
		{
			(*it)->Update();
			if ((*it)->IsFinish())
				it = m_enemiesShoots.erase(it);
			else
				it++;
		}
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

void	my::SchmupScene::UpdateColisions() throw (std::out_of_range)
{
	Shooter::ShootList::iterator itShoot;
	EnemiesPool::EnemiesList::iterator itEnemy;

	try
	{
		itShoot = m_playerShoots.begin();
		while (itShoot != m_playerShoots.end())
		{
			itEnemy = m_enemies.begin();
			while (itEnemy != m_enemies.end())
			{
				if ((*itEnemy)->IsIntersect((*itShoot)->GetHitBox()))
				{
					(*itEnemy)->TakeDamage((*itShoot)->GetDamage());
					(*itShoot)->TakeDamage(1);
					break;
				}
				else
					itEnemy++;
			}
			itShoot++;
		}
		itShoot = m_enemiesShoots.begin();
		while (itShoot != m_enemiesShoots.end())
		{
			if (m_player->IsIntersect((*itShoot)->GetHitBox()))
			{
				m_player->TakeDamage((*itShoot)->GetDamage());
				(*itShoot)->TakeDamage(1);
			}
			itShoot++;
		}
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

void	my::SchmupScene::UpdateObjects() throw (std::out_of_range)
{
	try
	{
		UpdateEnemiesPool();
		UpdatePlayer();
		UpdateEnemies();
		UpdateShoots();
		UpdateColisions();
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

void my::SchmupScene::draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept
{
	MainMenu::draw(target, states);
	states.transform *= getTransform();
	if (m_player)
		target.draw(*m_player, states);
	for (unsigned i = 0; i < m_enemies.size(); ++i)
		target.draw(*m_enemies[i], states);
	for (unsigned i = 0; i < m_playerShoots.size(); ++i)
		target.draw(*m_playerShoots[i], states);
	for (unsigned i = 0; i < m_enemiesShoots.size(); ++i)
		target.draw(*m_enemiesShoots[i], states);
}