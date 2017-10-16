#include "TextObject.hpp"

namespace	my
{
  TextObject::TextObject()
  {}

  void		TextObject::SetFont(const sf::Font & font)
  {
    m_text.setFont(font);
  }

  void		TextObject::SetText(const std::string & text)
  {
    m_text.setString(text);
  }

  void		TextObject::SetSize(int size)
  {

  }

  void		TextObject::SetColor(const sf::Color & color)
  {
    m_text.setFillColor(color);
  }

  void		TextObject::SetRotate(float rotate)
  {
    m_text.setRotation(rotate);
  }

  void		TextObject::SetScale(float scaleX, float scaleY)
  {
    m_text.setScale(scaleX, scaleY);
  }

  sf::Text	TextObject::GetText() const
  {
    return (m_text);
  }
}
