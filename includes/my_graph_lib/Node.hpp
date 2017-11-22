/*
 * Node.hpp
 *
 *  Created on: 16 oct. 2017
 *      Author: alexis
 */

#pragma once

#include <list>
#include <memory>
#include <stdexcept>
#include "SFML/Graphics.hpp"
#include "MoovableObject.hpp"

namespace my
{
	//! Class mère des entité dessinable.
	/*!
	Tous les objects dessinable hérite de Node.<br/>
	Il hérite de sf::Drawable et sf::Transformable afin de pouvoir être affiché dans une fenêtre et de se transformé.
	*/
  class Node : public sf::Drawable, public sf::Transformable, public MoovableObject
  {
  public:
	typedef std::shared_ptr<Node>	NodePtr;
	typedef std::list<NodePtr>		NodeList;

	virtual ~Node() noexcept {};

	//! Appel la fonction UpdateMovement
    virtual void Update();// throw (std::invalid_argument);

	//! Retourne la liste d'enfant de l'objet.
	NodeList		GetChilds() const noexcept;
	//! Détermine si l'objet est affichable.
	/*!
	<b>Valeur de retour</b><br/>
	Retourne true si l'objet est affichable, false sinon.
	*/
	bool		    IsVisible() const noexcept;
	//! Détermine si l'objet contient le point passé en argument
	/*!
	<b>Arguments</b><br/>
	point: Position du point à comparé.
	<br/><br/>
	<b>Valeur de retour</b><br/>
	Retourne true si le point est contenue dans l'objet, false sinon.
	*/
	virtual bool	IsIntersect(const sf::Vector2f & point) const noexcept = 0;
	//! Détermine si l'objet et le rectangle passé en argument ont une intersection.
	/*!
	<b>Arguments</b><br/>
	square: le rectangle à comparé.
	<br/><br/>
	<b>Valeur de retour</b><br/>
	retourne true si l'objet et square sont en intersection, false sinon.
	*/
	virtual bool	IsIntersect(const sf::FloatRect & square) const noexcept = 0;
	//! Retourne le rectangle physique de l'objet.
	virtual const sf::FloatRect GetHitBox() const noexcept = 0;

	//! Ajoute un nouvel enfant à la liste de l'objet.
	/*!
	<b>Arguments</b><br/>
	newChild: Pointeur sur le nouvel enfant.
	<br/><br/>
	<b>Exception</b><br/>
	std::invalid_argument: newChild est NULL.
	*/
	void		AddChild(NodePtr newChild) throw (std::invalid_argument);
	//! Ajoute un tableau d'enfant au tableau de l'objet.
	/*!
	<b>Arguments</b><br/>
	newChilds: Tableau des nouveaux enfants à ajouté.
	<br/><br/>
	<b>Exception</b><br/>
	std:invalid_argument: Un des enfants passé en arguments est NULL.
	*/
	void		AddChilds(NodeList newChilds) throw (std::invalid_argument);
	//! Change l'autorisation à se dessiner.
	void		SetVisible(bool visible) noexcept;

  protected:
	  //! Index de l'animation de déplacement.
	  static const std::string	MOOVING_ANIM_NAME;

	Node() noexcept;
	//! Dessine l'objet dans la fenetre.
	virtual void	draw(sf::RenderTarget &target, sf::RenderStates states) const;
	//! Met a jour la position de l'objet.
	/*!
	Appel UpdateDeplacement de sa classe mère, si m_onMove est true, appel la fonction move en utilisant la formule:<br/>
	m_direction * m_speed
	*/
	virtual void UpdateMovement() noexcept;

	//! Le tableau d'enfants.
	NodeList	m_childs;
	//! L'autorisation de se dessiner.
	bool		m_visible;
  };
} /* namespace my */
