#include "SpriteObject.hpp"

namespace	my
{
  SpriteObject::SpriteObject() noexcept
  {}

  bool    SpriteObject::IsIntersect(const sf::Vector2f & point) const noexcept
  {
    return m_sprite.getGlobalBounds().contains(point);
  }

  bool    SpriteObject::IsIntersect(const sf::FloatRect & square) const noexcept
  {
    return m_sprite.getGlobalBounds().intersects(square);
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

  const sf::Sprite	&SpriteObject::GetSprite() const noexcept
  {
	return (m_sprite);
  }
}
