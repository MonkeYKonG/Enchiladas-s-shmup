#pragma once

#include "Node.hpp"

namespace	my
{
  class TextObject : public Node
  {
  public:
    TextObject();
    virtual ~TextObject(){}

    void	SetFont(const sf::Font & font);
    void	SetText(const std::string & text);
    void	SetSize(int size);
    void	SetColor(const sf::Color & color);
    void	SetRotate(float rotate);
    void	SetScale(float scaleX, float scaleY);

    sf::Text	GetText() const;

  protected:
    sf::Text	m_text;
  };
}
