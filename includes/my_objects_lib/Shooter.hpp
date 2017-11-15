#pragma once

#include <vector>
#include <memory>
#include <map>
#include "my_graph_lib/XMLNode.hpp"
#include "Bullet.hpp"

namespace my
{
	class Shooter
	{
	public:
		typedef std::shared_ptr<Shooter> ShooterPtr;
		typedef std::vector<Bullet::BulletPtr> ShootList;
		typedef std::map<const std::string, XMLNode::XMLNodePtr> ShootNodes;

		bool CanShoot() const noexcept;
		const ShootList GetShootList() const throw (std::out_of_range, std::invalid_argument);
		const ShootNodes &GetShootNodes() const noexcept;
		const std::string &GetShootKey() const noexcept;

		void SetCanShoot(bool canShoot) noexcept;
		void SetShootNodes(const ShootNodes & shootNodes) noexcept;
		void AddShootNode(const std::string & str, XMLNode::XMLNodePtr newShootNode) throw (std::invalid_argument);
		void SetShootKey(const std::string & key) noexcept;

	protected:
		Shooter();
		virtual ~Shooter() {}

		void Update() noexcept;

		bool m_canShoot;
		ShootNodes m_shootNodes;
		std::string m_shootKey;
		unsigned m_shootFramerateMax;

	private:
		unsigned m_shootFramerate;
	};
}