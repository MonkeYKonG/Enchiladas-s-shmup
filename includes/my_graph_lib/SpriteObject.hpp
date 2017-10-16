#pragma once

#include "Node.hpp"

namespace	my
{
  class		SpriteObject : public Node
  {
  public:
    SpriteObject();
    virtual ~SpriteObject(){}

    void	SetTexture(const sf::Texture &texture);
    void	SetSize(int size);
    void	SetColor(const sf::Color &color);
    void	SetRotate(float rotate);
    void	SetScale(float scaleX, float scaleY);

    sf::Sprite	GetSprite() const;

  protected:
    sf::Sprite	m_sprite;
  };
}
