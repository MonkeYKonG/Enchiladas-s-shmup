#pragma once

#include "Node.hpp"

namespace	my
{
	//! Class contenant un sf::text et toutes les fonction pour le tranformé.
  class TextObject : public Node
  {
  public:
  	typedef std::shared_ptr<TextObject> TextObjectPtr;
  	
	TextObject() noexcept;
	virtual ~TextObject() noexcept {}

	//! Détermine si le point passé en argument est contenue dans le rectangle physique du texte.
	virtual bool	IsIntersect(const sf::Vector2f & point) const noexcept;
	//! Détermine le rectangle passé en argument est contenue dans le rectangle physique du texte.
	virtual bool	IsIntersect(const sf::FloatRect & square) const noexcept;
	//! Retourne le rectangle physique du texte.
	virtual const sf::FloatRect GetHitBox() const noexcept;

	//! Change la police à utilisé.
	void	SetFont(const sf::Font & font) noexcept;
	//! Change la valeur du texte.
	void	SetText(const std::string & text) noexcept;
	//! Change la taille des caractères.
	void	SetSize(int size) noexcept;
	//! Change la couleur du texte.
	void	SetColor(const sf::Color & color) noexcept;
	//! Change la rotation du texte.
	void	SetRotate(float rotate) noexcept;
	//! Change le zoom du texte.
	void	SetScale(float scaleX, float scaleY) noexcept;
	//! Change le zoom du texte.
	void    SetScale(const sf::Vector2f & scale) noexcept;
	//! Change l'origine du texte.
	void	SetOrigin(float origX, float origxY) noexcept;

	//! Retourne le texte.
	const sf::Text	&GetText() const noexcept;

  protected:
	  //! Dessine le texte.
  	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

	//! Text de l'objet.
	sf::Text	m_text;
  };
}
