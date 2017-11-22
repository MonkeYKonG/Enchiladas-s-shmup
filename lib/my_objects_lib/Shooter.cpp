#include "Shooter.hpp"
#include "ObjectPool.hpp"

my::Shooter::Shooter()
	: m_canShoot(false), m_shootFramerateMax(0), m_shootFramerate(0)
{}

void my::Shooter::Update() noexcept
{
	if (m_shootFramerate < m_shootFramerateMax)
		m_shootFramerate++;
}

bool my::Shooter::CanShoot() const noexcept
{
	return (m_canShoot);
}

const my::Shooter::ShootList my::Shooter::GetShootList() const throw (std::out_of_range, std::invalid_argument)
{
	ShootList shootList;
	XMLNode::XMLNodePtr curNode;

	try
	{
		curNode = m_shootNodes.at(m_shootKey);
		for (unsigned i = 0; i < curNode->GetChilds().size(); ++i)
		{
			shootList.push_back(ObjectPool::CreateBullet(curNode->GetChilds()[i]));
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
	return (shootList);
}

const my::Shooter::ShootNodes & my::Shooter::GetShootNodes() const noexcept
{
	return (m_shootNodes);
}

const std::string & my::Shooter::GetShootKey() const noexcept
{
	return (m_shootKey);
}

const unsigned my::Shooter::GetShootFramerateMax() const noexcept
{
	return (m_shootFramerateMax);
}

void	my::Shooter::SetCanShoot(bool canShoot) noexcept
{
	if (canShoot && m_shootFramerate >= m_shootFramerateMax)
	{
		m_shootFramerate = 0;
		m_canShoot = canShoot;
	}
	else
		m_canShoot = false;
}

void	my::Shooter::SetShootNodes(const ShootNodes & shootNodes) noexcept
{
	m_shootNodes = shootNodes;
}

void	my::Shooter::AddShootNode(const std::string & key, XMLNode::XMLNodePtr newShootNode) throw (std::invalid_argument)
{
	if (!newShootNode)
		throw (std::invalid_argument("Shooter: AddShootNode: null node"));
	m_shootNodes[key] = newShootNode;
}

void my::Shooter::SetShootKey(const std::string & key) noexcept
{
	m_shootKey = key;
}

void my::Shooter::SetShootFramerateMax(unsigned shootFramerateMax) noexcept
{
	m_shootFramerateMax = shootFramerateMax;
}
