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
#include "SFML/Graphics.hpp"

namespace my
{
  class Node : sf::Drawable, sf::Transformable
  {
  public:
    typedef std::shared_ptr<Node>	NodePtr;
    typedef std::list<NodePtr>			NodeList;

    virtual ~Node(){};

    NodeList		GetChilds() const;
    bool		IsVisible() const;
    bool		IsIntersect() const;

    void		AddChild(NodePtr newChild);
    void		AddChilds(NodeList newChilds);
    void		SetVisible(bool visible);

  protected:
    virtual void	draw(sf::RenderTarget &target, sf::RenderStates states) const;

    NodeList		m_childs;
    bool		m_visible;
  };
} /* namespace my */

#endif /* LIB_MY_GRAPH_LIB_NODE_HPP_ */
