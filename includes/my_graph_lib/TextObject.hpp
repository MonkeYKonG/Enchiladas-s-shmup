#pragma once

#include "Node.hpp"

namespace	my
{
  class TextObject : public Node
  {
  public:
  	typedef std::shared_ptr<TextObject> TextObjectPtr;
  	
	TextObject() noexcept;
	virtual ~TextObject() noexcept {}

	virtual bool	IsIntersect(const sf::Vector2f & point) const noexcept;
	virtual bool	IsIntersect(const sf::FloatRect & square) const noexcept;
	virtual const sf::FloatRect GetHitBox() const noexcept;

	void	SetFont(const sf::Font & font) noexcept;
	void	SetText(const std::string & text) noexcept;
	void	SetSize(int size) noexcept;
	void	SetColor(const sf::Color & color) noexcept;
	void	SetRotate(float rotate) noexcept;
	void	SetScale(float scaleX, float scaleY) noexcept;
	void    SetScale(const sf::Vector2f & scale) noexcept;
	void	SetOrigin(float origX, float origxY) noexcept;

	const sf::Text	&GetText() const noexcept;

  protected:
  	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

	sf::Text	m_text;
  };
}
