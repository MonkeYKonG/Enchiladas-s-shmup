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
	   m_text.setColor(color);
  }

  void		TextObject::SetRotate(float rotate) noexcept
  {
	   m_text.setRotation(rotate);
  }

  void		TextObject::SetScale(float scaleX, float scaleY) noexcept
  {
	   m_text.setScale(scaleX, scaleY);
  }

  void    TextObject::SetOrigin(float origX, float origY) noexcept
  {
      m_text.setOrigin(origX, origY);
  }

  const sf::Text	&TextObject::GetText() const noexcept
  {
	   return (m_text);
  }

  bool  TextObject::IsIntersect(const sf::Vector2f & point) const noexcept
  {
    return (m_text.getGlobalBounds().contains(point));
  }

  bool  TextObject::IsIntersect(const sf::FloatRect & square) const noexcept
  {
    return (m_text.getGlobalBounds().intersects(square));
  }

  void  TextObject::draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept
  {
    if (!m_visible)
      return;
    Node::draw(target, states);
    states.transform *= getTransform();
    target.draw(m_text, states);
  }
}