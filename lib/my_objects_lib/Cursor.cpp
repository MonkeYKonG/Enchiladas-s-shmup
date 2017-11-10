#include "Cursor.hpp"

namespace	my
{
	const std::string	Cursor::LEFT_CLICK_ANIM_NAME = "left_click";
	const std::string	Cursor::RIGHT_CLICK_ANIM_NAME = "right_click";

	Cursor::Cursor()
	{}

	Cursor::~Cursor()
	{}

	void	Cursor::Update() throw (std::out_of_range)
	{
		try
		{
			if (!m_animations.empty())
			{
				if (!m_onAnimation && AnimationExist(DEFAULT_ANIM_NAME))
					SetAnimIndex(DEFAULT_ANIM_NAME);
				if (AnimationExist(LEFT_CLICK_ANIM_NAME) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
					SetAnimIndex(LEFT_CLICK_ANIM_NAME);
				else if (AnimationExist(RIGHT_CLICK_ANIM_NAME) && sf::Mouse::isButtonPressed(sf::Mouse::Right))
					SetAnimIndex(RIGHT_CLICK_ANIM_NAME);
				m_onAnimation = true;
			}
			SpriteObject::Update();
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
	}

	void	Cursor::Update(const sf::Vector2f & mousePos) throw (std::out_of_range)
	{
		try
		{
			if (!m_onAnimation && AnimationExist(MOOVING_ANIM_NAME) && mousePos != getPosition())
			{
				m_onAnimation = true;
				SetAnimIndex(MOOVING_ANIM_NAME);	
			}
			setPosition(mousePos);
			Update();
		}
		catch (const std::out_of_range & e)
		{
			throw (e);
		}
	}
}