#pragma once

#include "Node.hpp"

namespace	my
{
  class TextObject : public Node
  {
  public:
	TextObject() noexcept;
	virtual ~TextObject() noexcept {}

	void	SetFont(const sf::Font & font) noexcept;
	void	SetText(const std::string & text) noexcept;
	void	SetSize(int size) noexcept;
	void	SetColor(const sf::Color & color) noexcept;
	void	SetRotate(float rotate) noexcept;
	void	SetScale(float scaleX, float scaleY) noexcept;
	void    SetScale(const sf::Vector2f & scale) noexcept;

	const sf::Text	&GetText() const noexcept;

  protected:
	sf::Text	m_text;
  };
}
