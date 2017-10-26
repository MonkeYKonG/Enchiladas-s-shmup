#pragma once

#include "Node.hpp"

namespace	my
{
  class		SpriteObject : public Node
  {
  public:
  	typedef std::shared_ptr<SpriteObject> SpriteObjectPtr;
  	
	SpriteObject() noexcept;
	virtual ~SpriteObject() noexcept {}

	virtual bool IsIntersect(const sf::Vector2f & point) const noexcept;
	virtual bool IsIntersect(const sf::FloatRect & square) const noexcept;

	void	SetTexture(const sf::Texture & texture) noexcept;
	void	SetColor(const sf::Color & color) noexcept;
	void	SetRotate(float rotate) noexcept;
	void	SetScale(float scaleX, float scaleY) noexcept;
	void    SetScale(const sf::Vector2f & scale) noexcept;

	const sf::Sprite &GetSprite() const noexcept;

  protected:
	sf::Sprite	m_sprite;
  };
}
