/*
 * Node.hpp
 *
 *  Created on: 16 oct. 2017
 *      Author: alexis
 */

#ifndef LIB_MY_GRAPH_LIB_NODE_HPP_
#define LIB_MY_GRAPH_LIB_NODE_HPP_

#include <list>
#include <memory>
#include <stdexcept>
#include "SFML/Graphics.hpp"

namespace my
{
  class Node : public sf::Drawable, public sf::Transformable
  {
  public:
    typedef std::shared_ptr<Node>	NodePtr;
    typedef std::list<NodePtr>		NodeList;

    virtual ~Node() noexcept {};

    NodeList		GetChilds() const noexcept;
    bool		    IsVisible() const noexcept;
    virtual bool	IsIntersect() const noexcept = 0;

    void		AddChild(NodePtr newChild) throw (std::invalid_argument);
    void		AddChilds(NodeList newChilds) throw (std::invalid_argument);
    void		SetVisible(bool visible) noexcept;

  protected:
    Node() noexcept;
    virtual void	draw(sf::RenderTarget &target, sf::RenderStates states) const;

    NodeList	m_childs;
    bool		m_visible;
  };
} /* namespace my */

#endif /* LIB_MY_GRAPH_LIB_NODE_HPP_ */
