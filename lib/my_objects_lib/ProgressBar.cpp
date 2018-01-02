#include "ProgressBar.hpp"

my::ProgressBar::ProgressBar()
	: m_curValue(0), m_maxValue(0)
{}

unsigned my::ProgressBar::GetCurValue() const noexcept
{
	return (*m_curValue);
}

unsigned my::ProgressBar::GetMaxValue() const noexcept
{
	return (*m_maxValue);
}

const sf::Sprite &my::ProgressBar::GetBackgroundSprite() const noexcept
{
	return (m_background);
}

void my::ProgressBar::SetCurValue(unsigned * curValue) noexcept
{
	m_curValue = curValue;
}

void my::ProgressBar::SetMaxValue(unsigned * maxValue) noexcept
{
	m_maxValue = maxValue;
}

void my::ProgressBar::SetValues(unsigned * curValue, unsigned * maxValue) noexcept
{
	SetCurValue(curValue);
	SetMaxValue(maxValue);
}

void my::ProgressBar::SetBackgroundTexture(const sf::Texture & texture) noexcept
{
	m_background.setTexture(texture);
}

void my::ProgressBar::SetBackgroundSize(const sf::IntRect & rect) noexcept
{
	m_background.setTextureRect(rect);
}

void my::ProgressBar::Update() throw (std::exception)
{
	sf::IntRect textureRect;
	
	if (m_curValue == 0 || m_maxValue == 0)
		return;
	textureRect = m_background.getTextureRect();
	textureRect.width = *m_curValue * textureRect.width / *m_maxValue;
	m_sprite.setTextureRect(textureRect);
}

void my::ProgressBar::draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept
{
	sf::RenderStates transromedStates;

	if (!m_visible)
		return;
	transromedStates = states;
	transromedStates.transform *= getTransform();
	//target.draw(m_background, transromedStates);
	SpriteObject::draw(target, states);
}