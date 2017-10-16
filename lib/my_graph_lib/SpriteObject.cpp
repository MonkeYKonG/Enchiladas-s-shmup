#include "SpriteObject.hpp"

namespace	my
{
  SpriteObject::SpriteObject()
  {}

  void		SpriteObject::SetTexture(const sf::Texture & texture)
  {
    m_sprite.setTexture(texture);
  }

  void		SpriteObject::SetSize(int size)
  {

  }

  void		SpriteObject::SetColor(const sf::Color & color)
  {
    m_sprite.setColor(color);
  }

  void		SpriteObject::SetRotate(float rotate)
  {
    m_sprite.setRotation(rotate);
  }

  void		SpriteObject::SetScale(float scaleX, float scaleY)
  {
    m_sprite.setScale(scaleX, scaleY);
  }

  sf::Sprite	SpriteObject::GetSprite() const
  {
    return (m_sprite);
  }
}
