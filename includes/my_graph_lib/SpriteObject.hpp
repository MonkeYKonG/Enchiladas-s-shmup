#pragma once

#include "Node.hpp"
#include "AnimatedObject.hpp"

namespace	my
{
	//! Class contenant un sf::sprite et les fonction pour le transformer et l'afficher.
  class		SpriteObject : public Node, public AnimatedObject
  {
  public:
  	typedef std::shared_ptr<SpriteObject> SpriteObjectPtr;
  	
	SpriteObject() noexcept;
	virtual ~SpriteObject() noexcept {}

	//! Détermine si le point passé en argument est contenue dans le sprite.
	virtual bool IsIntersect(const sf::Vector2f & point) const noexcept;
	// Détermine si le resctangle passé en argument est en intersectiona vec le sprite.
	virtual bool IsIntersect(const sf::FloatRect & square) const noexcept;
	//! Retourne le rectangle physique du sprite.
	virtual const sf::FloatRect GetHitBox() const noexcept;

	//! Met a jour l'objet appel les fonction Update des class mères.
	virtual void Update() throw (std::out_of_range);

	//! Change la texture du sprite.
	void	SetTexture(const sf::Texture & texture) noexcept;
	//! Change la couleur du sprite.
	void	SetColor(const sf::Color & color) noexcept;
	//! Change la rotation du sprite.
	void	SetRotate(float rotate) noexcept;
	//! Change le zoom du sprite.
	void	SetScale(float scaleX, float scaleY) noexcept;
	//! Change le zoom du sprite.
	void    SetScale(const sf::Vector2f & scale) noexcept;
	//! Change l'origine du sprite.
	void	SetOrigin(float origX, float origY) noexcept;
	//! Change la tuile d'aniamtion du rectangle.
	void	SetSubrect(const sf::IntRect & subrect) noexcept;

	//! Retourne le sprite de l'objet.
	const sf::Sprite &GetSprite() const noexcept;

  protected:
	  //! Appel UpdateAniation de la class mère et cahnge la tuile d'animation du sprite.
	  virtual void UpdateAnimation() throw (std::out_of_range);

	  //! Dessine le sprite.
  	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const noexcept;

	//! Sprite de l'objet.
	sf::Sprite	m_sprite;
  };
}
