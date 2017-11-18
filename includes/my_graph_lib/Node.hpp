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
  class Node : public sf::Drawable, public sf::Transformable, public MoovableObject
  {
  public:
	typedef std::shared_ptr<Node>	NodePtr;
	typedef std::list<NodePtr>		NodeList;

	virtual ~Node() noexcept {};

	virtual void Update();

	NodeList		GetChilds() const noexcept;
	bool		    IsVisible() const noexcept;
	virtual bool	IsIntersect(const sf::Vector2f & point) const noexcept = 0;
	virtual bool	IsIntersect(const sf::FloatRect & square) const noexcept = 0;
	virtual const sf::FloatRect GetHitBox() const noexcept = 0;

	void		AddChild(NodePtr newChild) throw (std::invalid_argument);
	void		AddChilds(NodeList newChilds) throw (std::invalid_argument);
	void		SetVisible(bool visible) noexcept;

  protected:
	  static const std::string	MOOVING_ANIM_NAME;

	Node() noexcept;
	virtual void	draw(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void UpdateMovement() noexcept;

	NodeList	m_childs;
	bool		m_visible;
  };
} /* namespace my */
