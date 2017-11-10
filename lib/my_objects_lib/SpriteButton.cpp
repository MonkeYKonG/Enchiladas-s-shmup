#include "SpriteButton.hpp"

my::SpriteButton::SpriteButton()
{}

my::SpriteButton::~SpriteButton()
{}

void	my::SpriteButton::Update() throw (std::out_of_range)
{
	try
	{
		SpriteObject::Update();
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
}