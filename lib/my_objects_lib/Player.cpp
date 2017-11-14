#include "Player.hpp"

my::Player::Player()
{}

void	my::Player::Update() throw (std::out_of_range)
{
	try
	{
		SpriteObject::Update();
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}