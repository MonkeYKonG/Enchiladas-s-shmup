/*
 * Node.cpp
 *
 *  Created on: 16 oct. 2017
 *      Author: alexis
 */

#include "Node.hpp"
#include "MessagesException.hpp"

namespace my {
	Node::Node() noexcept
	: m_visible(true)
	{}

	Node::NodeList	Node::GetChilds() const noexcept
	{
	return (m_childs);
	}

	bool			Node::IsVisible() const noexcept
	{
	return (m_visible);
	}

	void			Node::AddChild(NodePtr newChild) throw (std::invalid_argument)
	{
	if (!newChild)
		throw (std::invalid_argument(MessagesException::NullPtr("Node::AddChild(NodePtr newChild)", "newChild")));
	m_childs.push_back(newChild);
	}

	void			Node::AddChilds(NodeList newChilds) throw (std::invalid_argument)
	{
	for (auto it = newChilds.begin(); it != newChilds.end(); ++it)
	{
		if (!(*it))
			throw (std::invalid_argument(MessagesException::NullPtr("Node::AddChilds(NodeList newChilds)", "newChild::iterator")));
		m_childs.push_back(*it);
	}
	}

	void			Node::SetVisible(bool visible) noexcept
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
