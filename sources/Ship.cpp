#include "Ship.hpp"

bool my::schmup::Ship::IsIntersect(const sf::Vector2f & point) const noexcept
{
	return (false);
}

bool my::schmup::Ship::IsIntersect(const sf::FloatRect & suqare) const noexcept
{
	return (false);
}

const sf::FloatRect my::schmup::Ship::GetHitBox() const noexcept
{
	return (sf::FloatRect());
}

void my::schmup::Ship::AddModule(ShipModule::ShipModulePtr newModule) noexcept
{
	m_modules.push_back(newModule);
}

void my::schmup::Ship::draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept
{
	states.transform = getTransform();
	for (auto it = m_modules.begin(); it != m_modules.end(); ++it)
	{
		if (it->get()->IsAlive())
			target.draw(*it->get(), states);
	}
}