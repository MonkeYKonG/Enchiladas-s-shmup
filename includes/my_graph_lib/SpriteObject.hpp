#pragma once

#include "Node.hpp"
#include "AnimatedObject.hpp"

namespace	my
{
  class		SpriteObject : public Node, public AnimatedObject
  {
  public:
  	typedef std::shared_ptr<SpriteObject> SpriteObjectPtr;
  	
	SpriteObject() noexcept;
	virtual ~SpriteObject() noexcept {}

	virtual bool IsIntersect(const sf::Vector2f & point) const noexcept;
	virtual bool IsIntersect(const sf::FloatRect & square) const noexcept;

	virtual void Update() throw (std::out_of_range);

	void	SetTexture(const sf::Texture & texture) noexcept;
	void	SetColor(const sf::Color & color) noexcept;
	void	SetRotate(float rotate) noexcept;
	void	SetScale(float scaleX, float scaleY) noexcept;
	void    SetScale(const sf::Vector2f & scale) noexcept;
	void	SetOrigin(float origX, float origY) noexcept;
	void	SetSubrect(const sf::IntRect & subrect) noexcept;

	const sf::Sprite &GetSprite() const noexcept;

  protected:
	  virtual void UpdateAnimation() throw (std::out_of_range);

  	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

	sf::Sprite	m_sprite;
  };
}
