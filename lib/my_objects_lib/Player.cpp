#include "Player.hpp"

my::Player::Player()
{}

void	my::Player::Update() throw (std::out_of_range)
{
	try
	{
		CheckForInput();
		SpriteObject::Update();
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

const my::Player::InputsList & my::Player::GetInputsList() const noexcept
{
	return (m_inputs);
}

void my::Player::AddInputs(const Player::InputPair & newInput) noexcept
{
	m_inputs.push_back(newInput);
}

void my::Player::SetInputs(const Player::InputsList & inputs) noexcept
{
	m_inputs = inputs;
}

void my::Player::UpdateMovement() noexcept
{
	sf::Vector2f direction;

	if (m_curentDeplacement[Direction::UP])
		direction.y -= 1;
	if (m_curentDeplacement[Direction::DOWN])
		direction.y += 1;
	if (m_curentDeplacement[Direction::LEFT])
		direction.x -= 1;
	if (m_curentDeplacement[Direction::RIGHT])
		direction.x += 1;
	m_direction = direction = NormalizeVector(direction);
	m_onDeplacement = true;
	SpriteObject::UpdateMovement();
}

void my::Player::CheckForInput() noexcept
{
	for (unsigned i = 0; i < CUR_DEPL_SIZE; ++i)
		m_curentDeplacement[i] = false;
	for (unsigned i = 0; i < m_inputs.size(); ++i)
		if (sf::Keyboard::isKeyPressed(m_inputs[i].first))
			m_curentDeplacement[m_inputs[i].second] = true;
}