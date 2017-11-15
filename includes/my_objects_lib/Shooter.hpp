#pragma once

#include <vector>
#include <memory>
#include <map>
#include "my_graph_lib/XMLNode.hpp"

namespace my
{
	class Shooter
	{
	public:
		typedef std::shared_ptr<Shooter> ShooterPtr;
		typedef std::vector<int> ShootList;
		typedef std::map<const std::string, XMLNode::XMLNodePtr> ShootNodes;

		bool CanShoot() const noexcept;
		const ShootList GetShootList() const throw (std::out_of_range);
		const ShootNodes &GetShootNodes() const noexcept;
		const std::string &GetShootKey() const noexcept;

		void SetCanShoot(bool canShoot) noexcept;
		void SetShootNodes(const ShootNodes & shootNodes) noexcept;
		void AddShootNode(std::string & str, XMLNode::XMLNodePtr newShootNode) throw (std::invalid_argument);
		void SetShootKey(const std::string & key) noexcept;

	protected:
		Shooter();
		virtual ~Shooter() {}

		bool m_canShoot;
		ShootNodes m_shootNodes;
		std::string m_shootKey;
	};
}