#include "SpriteButton.hpp"
#include "my_graph_lib/InputsManager.hpp"

const std::string	my::SpriteButton::ON_CLICK_ANIM_NAME = "on_click";
const std::string	my::SpriteButton::ON_MOUSE_OVER_ANIM_NAME = "on_mouse_over";

my::SpriteButton::SpriteButton()
	: m_isMouseOvered(false), m_isClicked(false)
{}

my::SpriteButton::~SpriteButton()
{}

void my::SpriteButton::Update(const sf::Vector2f & mousePos) throw(std::out_of_range)
{
	sf::Vector2f transformedMousePos;

	transformedMousePos = getTransform().getInverse().transformPoint(mousePos);
	try
	{
		UpdateMouse(transformedMousePos);
		Update();
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

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

void	my::SpriteButton::UpdateMouse(const sf::Vector2f & mousePos)
{
	m_isMouseOvered = false;
	m_isClicked = false;
	if (IsIntersect(mousePos))
	{
		m_isMouseOvered = true;
		if (InputsManager::IsButtonPressed(sf::Mouse::Left))
			m_isClicked = true;
	}
}

void my::SpriteButton::UpdateAnimation() throw(std::out_of_range)
{
	if (m_animations.empty() || m_onAnimation)
		return;
	m_onAnimation = true;
	if (m_isMouseOvered)
	{
		if (m_isClicked && AnimationExist(ON_CLICK_ANIM_NAME))
			SetAnimIndex(ON_CLICK_ANIM_NAME);
		else if (AnimationExist(ON_MOUSE_OVER_ANIM_NAME))
			SetAnimIndex(ON_MOUSE_OVER_ANIM_NAME);
	}
	else if (AnimationExist(DEFAULT_ANIM_NAME))
		SetAnimIndex(DEFAULT_ANIM_NAME);
	try
	{
		SpriteObject::UpdateAnimation();
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

bool my::SpriteButton::IsMouseOvered() const noexcept
{
	return (m_isMouseOvered);
}

bool my::SpriteButton::IsClicked() const noexcept
{
	return (m_isClicked);
}

my::TextObject::TextObjectPtr my::SpriteButton::GetText() const noexcept
{
	return (m_text);
}

void my::SpriteButton::SetText(TextObject::TextObjectPtr newText) noexcept
{
	m_text = newText;
	m_text->SetOrigin(m_text->GetText().getGlobalBounds().width / 2, m_text->GetText().getGlobalBounds().height / 2);
}

void my::SpriteButton::draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept
{
	if (!m_visible)
		return;
	SpriteObject::draw(target, states);
	states.transform *= getTransform();
	if (m_text)
		target.draw(*m_text, states);
}