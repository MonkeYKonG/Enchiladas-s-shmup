#include "Shooter.hpp"
#include "ObjectPool.hpp"

my::Shooter::Shooter()
	: m_canShoot(false)
{}

bool my::Shooter::CanShoot() const noexcept
{
	return (m_canShoot);
}

const my::Shooter::ShootList my::Shooter::GetShootList() const throw (std::out_of_range)
{
	ShootList shootList;
	XMLNode::XMLNodePtr curNode;

	try
	{
		curNode = m_shootNodes.at(m_shootKey);
		for (unsigned i = 0; i < curNode->GetChilds().size(); ++i)
			;// shootList.push_back(ObjectPool::CreateBullet(curNode->GetChilds()[i]));
	}
	catch (const std::out_of_range & e)
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

void	my::Shooter::SetCanShoot(bool canShoot) noexcept
{
	m_canShoot = canShoot;
}

void	my::Shooter::SetShootNodes(const ShootNodes & shootNodes) noexcept
{
	m_shootNodes = shootNodes;
}

void	my::Shooter::AddShootNode(std::string & key, XMLNode::XMLNodePtr newShootNode) throw (std::invalid_argument)
{
	if (!newShootNode)
		throw (std::invalid_argument("Shooter: AddShootNode: null node"));
	m_shootNodes[key] = newShootNode;
}

void my::Shooter::SetShootKey(const std::string & key) noexcept
{
	m_shootKey = key;
}
