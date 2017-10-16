/*
 * Node.cpp
 *
 *  Created on: 16 oct. 2017
 *      Author: alexis
 */

#include "Node.hpp"

namespace my {
  Node::NodeList	Node::GetChilds()
  {
    return (m_childs);
  }

  bool			Node::IsVisible()
  {
    return (m_visible);
  }
  bool			Node::IsIntersect()
  {
    return (false);
  }

  void			Node::AddChild(NodePtr newChild)
  {
    m_childs.push_back(newChild);
  }

  void			Node::AddChilds(NodeList newChilds)
  {
    for (auto it = newChilds.begin(); it != newChilds.end(); ++it)
      m_childs.push_back(*it);
  }

  void			Node::SetVisible(bool visible)
  {
    m_visible = visible;
  }

  void			Node::draw(sf::RenderTarget & target, sf::RenderStates states) const
  {
    if (!m_visible)
      return;

    states.transform *= getTransform();
    for (auto it = m_childs.begin(); it != m_childs.end(); ++it)
      target.draw(*(*it), states);
  }
} /* namespace my */
