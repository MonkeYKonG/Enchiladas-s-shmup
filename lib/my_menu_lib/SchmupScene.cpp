#include "SchmupScene.hpp"
#include "my_objects_lib/ObjectPool.hpp"

const std::string my::SchmupScene::SCENE_PLAYER_NODE = "player";
const std::string my::SchmupScene::SCENE_STAGES_NODE = "stages";
const std::string my::SchmupScene::SCENE_ENEMIES_NODE = "enemies";

my::SchmupScene::SchmupScene()
{}

const my::SceneReturnValue my::SchmupScene::Update(const sf::Vector2i & mousePos) throw(std::exception)
{
	SceneReturnValue returnValue;

	try
	{
		returnValue = MainMenu::Update(mousePos);
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

void	my::SchmupScene::UpdateEnemiesPool() throw (std::out_of_range, std::invalid_argument)
{
	EnemiesPool::EnemiesList newEnemies;

	try
	{
		newEnemies = GeneratingEnemiesList();
		AddingNewEnemies(newEnemies);
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

void	my::SchmupScene::UpdatePlayer() throw (std::exception)
{
	try
	{
		if (m_player)
		{
			UpdatingPlayer();
			if (m_player->CanShoot())
				TriggerPlayerShooting();
		}
	}
	catch (const std::exception & e)
	{
		throw (e);
	}
}

void	my::SchmupScene::UpdateEnemies() throw (std::exception)
{
	EnemiesPool::EnemiesList::iterator it;
	try
	{
		it = m_enemies.begin();
		while (it != m_enemies.end())
		{
			UpdatingEnemy(it);
			if ((*it)->IsFinish())
				TriggerRemoveEnemy(it);
			else
				it++;
		}
	}
	catch (const std::exception & e)
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
			UpdatingPlayerBullet(it);
			if ((*it)->IsFinish())
				TriggerRemovePlayerBullet(it);
			else
				it++;
		}
		it = m_enemiesShoots.begin();
		while (it != m_enemiesShoots.end())
		{
			UpdatingEnemiesBullet(it);
			if ((*it)->IsFinish())
				TriggerRemoveEnemiesBullet(it);
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
					TriggerEnemyIsDamaged(itShoot, itEnemy);
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
				TriggerPlayerIsDamaged(itShoot);
			itShoot++;
		}
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

void	my::SchmupScene::UpdateObjects() throw (std::exception)
{
	try
	{
		UpdateEnemiesPool();
		UpdatePlayer();
		UpdateEnemies();
		UpdateShoots();
		UpdateColisions();
	}
	catch (const std::exception & e)
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

const my::EnemiesPool::EnemiesList my::SchmupScene::GeneratingEnemiesList() throw (std::out_of_range, std::invalid_argument)
{
	return(m_enemiesPool.Update(m_enemies.empty()));
}

void my::SchmupScene::AddingNewEnemies(const EnemiesPool::EnemiesList & newEnemies) noexcept
{
	for (unsigned i = 0; i < newEnemies.size(); ++i)
		AddingNewEnemy(newEnemies[i]);
}

void my::SchmupScene::AddingNewEnemy(Enemy::EnemyPtr newEnemy) noexcept
{
	m_enemies.push_back(newEnemy);
}

void my::SchmupScene::UpdatingPlayer() throw (std::exception)
{
	m_player->Update();
}

void my::SchmupScene::TriggerPlayerShooting() throw (std::out_of_range, std::invalid_argument)
{
	Shooter::ShootList newShoots;

	try
	{
		newShoots = GeneratingPlayerBullets();
		AddingNewPlayerBullets(newShoots);
		m_player->SetCanShoot(false);
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

const my::Shooter::ShootList my::SchmupScene::GeneratingPlayerBullets() throw (std::out_of_range, std::invalid_argument)
{
	try
	{
		return (m_player->GetShootList());
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

void my::SchmupScene::AddingNewPlayerBullets(Shooter::ShootList & newBullets) noexcept
{
	for (unsigned i = 0; i < newBullets.size(); ++i)
	{
		PreparingPlayerBuller(newBullets[i]);
		AddingPlayerBullet(newBullets[i]);
	}
}

void my::SchmupScene::PreparingPlayerBuller(Bullet::BulletPtr newBullet) noexcept
{
	newBullet->setPosition(m_player->getPosition());
}

void my::SchmupScene::AddingPlayerBullet(Bullet::BulletPtr newBullet) noexcept
{
	m_playerShoots.push_back(newBullet);
}

void my::SchmupScene::UpdatingEnemy(EnemiesPool::EnemiesList::iterator & enemyIt) throw (std::exception)
{
	try
	{
		(*enemyIt)->Update();
	}
	catch (const std::exception & e)
	{
		throw (e);
	}
}

void my::SchmupScene::TriggerRemoveEnemy(EnemiesPool::EnemiesList::iterator & enemyIt) noexcept
{
	enemyIt = m_enemies.erase(enemyIt);
}

void my::SchmupScene::UpdatingPlayerBullet(Shooter::ShootList::iterator & bulletIt) throw (std::exception)
{
	try
	{
		(*bulletIt)->Update();
	}
	catch (const std::exception & e)
	{
		throw (e);
	}
}

void my::SchmupScene::TriggerRemovePlayerBullet(Shooter::ShootList::iterator & bulletIt) noexcept
{
	bulletIt = m_playerShoots.erase(bulletIt);
}

void my::SchmupScene::UpdatingEnemiesBullet(Shooter::ShootList::iterator & bulletIt) throw (std::exception)
{
	try
	{
		(*bulletIt)->Update();
	}
	catch (const std::exception & e)
	{
		throw (e);
	}
}

void my::SchmupScene::TriggerRemoveEnemiesBullet(Shooter::ShootList::iterator & bulletIt) noexcept
{
	bulletIt = m_enemiesShoots.erase(bulletIt);
}

void my::SchmupScene::TriggerEnemyIsDamaged(Shooter::ShootList::iterator & bulletIt, EnemiesPool::EnemiesList::iterator & enemyIt) noexcept
{
	(*enemyIt)->TakeDamage((*bulletIt)->GetDamage());
	(*bulletIt)->TakeDamage(1);
}

void my::SchmupScene::TriggerPlayerIsDamaged(Shooter::ShootList::iterator & bulletIt) noexcept
{
	m_player->TakeDamage((*bulletIt)->GetDamage());
	(*bulletIt)->TakeDamage(1);
}