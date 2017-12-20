#include "Player.hpp"

my::Player::Player()
{}

void	my::Player::Update() throw (std::out_of_range)
{
	try
	{
		Shooter::Update();
		CheckForInput();
		SpriteObject::Update();
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

const my::Player::InputsDeplacementList & my::Player::GetInputsDeplacementList() const noexcept
{
	return (m_inputsDeplacement);
}

const my::Player::InputsShootList & my::Player::GetInputsShootList() const noexcept
{
	return (m_inputsShoot);
}

void my::Player::AddInputDeplacement(const Player::InputDeplacement & newInput) noexcept
{
	m_inputsDeplacement.push_back(newInput);
}

void my::Player::SetInputsDeplacement(const Player::InputsDeplacementList & inputs) noexcept
{
	m_inputsDeplacement = inputs;
}

void my::Player::AddInputShoot(const InputShoot & newInput) noexcept
{
	m_inputsShoot.push_back(newInput);
}

void my::Player::SetInputsShoot(const InputsShootList & inputs) noexcept
{
	m_inputsShoot = inputs;
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

void my::Player::UpdateAnimation() throw(std::out_of_range)
{
	try
	{
		if (!m_onAnimation && AnimationExist(DEFAULT_ANIM_NAME))
		{
			m_onAnimation = true;
			SetAnimIndex(DEFAULT_ANIM_NAME);
		}
		SpriteObject::UpdateAnimation();
	}
	catch (const std::out_of_range & e)
	{
		throw (e);
	}
}

void my::Player::CheckForInput() noexcept
{
	for (unsigned i = 0; i < CUR_DEPL_SIZE; ++i)
		m_curentDeplacement[i] = false;
	for (unsigned i = 0; i < m_inputsDeplacement.size(); ++i)
		if (sf::Keyboard::isKeyPressed(m_inputsDeplacement[i].first))
			m_curentDeplacement[m_inputsDeplacement[i].second] = true;
	for (unsigned i = 0; i < m_inputsShoot.size(); ++i)
		if (!m_canShoot && sf::Keyboard::isKeyPressed(m_inputsShoot[i].first))
		{
			m_shootKey = m_inputsShoot[i].second;
			SetCanShoot(true);
		}
}

unsigned my::Player::ComputeBulletDamage(Bullet::BulletPtr bullet) const noexcept
{
	return (bullet->GetDamage() * m_atk);
}
