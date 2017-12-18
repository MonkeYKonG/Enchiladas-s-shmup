#include "ShipModule.hpp"

my::schmup::ShipModule::ShipModule()
	: m_regenFramerate(0), m_regenCurFramerate(0)
{}

my::schmup::ShipModule::~ShipModule()
{}

void my::schmup::ShipModule::SetShipPosition(const sf::Vector2i & shipPosition) noexcept
{
	m_shipPosition = shipPosition;
}