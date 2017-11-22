#include "SpriteObject.hpp"

namespace	my
{
  SpriteObject::SpriteObject() noexcept
  {}

  bool    SpriteObject::IsIntersect(const sf::Vector2f & point) const noexcept
  {
    return GetHitBox().contains(point);
  }

  bool    SpriteObject::IsIntersect(const sf::FloatRect & square) const noexcept
  {
    return GetHitBox().intersects(square);
  }

  const sf::FloatRect SpriteObject::GetHitBox() const noexcept
  {
	  sf::FloatRect hitBox;

	  hitBox = m_sprite.getGlobalBounds();
	  hitBox.left = getPosition().x;
	  hitBox.top = getPosition().y;
	  return (hitBox);
  }

  void		SpriteObject::UpdateAnimation() throw (std::out_of_range)
  {
	  if (m_onAnimation)
	  {
		  m_sprite.setTextureRect(GetCurentRect());
	  }
	  try
	  {
		  AnimatedObject::UpdateAnimation();
	  }
	  catch (const std::out_of_range & e)
	  {
		  throw (e);
	  }
  }

  void	SpriteObject::Update() throw (std::out_of_range)
  {
	  Node::Update();
	  try
	  {
		  UpdateAnimation();
	  }
	  catch (const std::out_of_range & e)
	  {
		  throw (e);
	  }
  }

  void		SpriteObject::SetTexture(const sf::Texture & texture) noexcept
  {
    m_sprite.setTexture(texture);
  }

  void		SpriteObject::SetColor(const sf::Color & color) noexcept
  {
	  m_sprite.setColor(color);
  }

  void	    SpriteObject::SetRotate(float rotate) noexcept
  {
    m_sprite.setRotation(rotate);
  }

  void      SpriteObject::SetScale(float scaleX, float scaleY) noexcept
  {
    m_sprite.setScale(scaleX, scaleY);
  }

  void      SpriteObject::SetScale(const sf::Vector2f &scale) noexcept
  {
    m_sprite.setScale(scale);
  }

  void    SpriteObject::SetOrigin(float origX, float origY) noexcept
  {
    m_sprite.setOrigin(origX, origY);
  }

  void    SpriteObject::SetSubrect(const sf::IntRect & subrect) noexcept
  {
    m_sprite.setTextureRect(subrect);
  }

  const sf::Sprite	&SpriteObject::GetSprite() const noexcept
  {
    return (m_sprite);
  }

  void SpriteObject::draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept
  {
    if (!m_visible)
      return;
    Node::draw(target, states);
    states.transform *= getTransform();
    target.draw(m_sprite, states);
  }
}
