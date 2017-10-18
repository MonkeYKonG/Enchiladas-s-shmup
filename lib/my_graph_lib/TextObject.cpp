#include "TextObject.hpp"

namespace	my
{
  TextObject::TextObject() noexcept
  {}

  void		TextObject::SetFont(const sf::Font & font) noexcept
  {
	m_text.setFont(font);
  }

  void		TextObject::SetText(const std::string & text) noexcept
  {
	m_text.setString(text);
  }

  void		TextObject::SetSize(int size) noexcept
  {
	m_text.setCharacterSize(size);
  }

  void		TextObject::SetColor(const sf::Color & color) noexcept
  {
	m_text.setFillColor(color);
  }

  void		TextObject::SetRotate(float rotate) noexcept
  {
	m_text.setRotation(rotate);
  }

  void		TextObject::SetScale(float scaleX, float scaleY) noexcept
  {
	m_text.setScale(scaleX, scaleY);
  }

  const sf::Text	&TextObject::GetText() const noexcept
  {
	return (m_text);
  }
}