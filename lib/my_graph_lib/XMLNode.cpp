#include "XMLNode.hpp"

namespace	my
{
	XMLNode::XMLNode(const ContentList & contents) noexcept
	{}

	XMLNode::XMLNodePtr XMLNode::create(const ContentList & contents) noexcept
	{
		return (XMLNodePtr(new XMLNode(contents)));
	}

	const XMLNode::NodeList &XMLNode::GetChilds() const noexcept
	{
		return (m_childs);
	}

	XMLNode::XMLNodePtr XMLNode::GetChild(int index) const throw (std::out_of_range)
	{
		return (m_childs[index]);
	}

	XMLNode::XMLNodePtr XMLNode::GetChild(const std::string & key) const throw (std::out_of_range)
	{
		for (unsigned i = 0; i < m_childs.size(); ++i)
			if (m_childs[i]->GetName() == key)
				return (m_childs[i]);
		return (XMLNodePtr(0));
	}

	const std::string &XMLNode::GetName() const noexcept
	{
		return (m_name);
	}

	const XMLNode::ContentList &XMLNode::GetContents() const noexcept
	{
		return (m_contents);
	}

	const XMLNode::NodeContent &XMLNode::GetContent(const std::string & key) const throw (std::out_of_range)
	{
		for (unsigned i = 0; i < m_contents.size(); ++i)
			if (m_contents[i].first == key)
				return (m_contents[i]);
	}

	void XMLNode::AddChild(XMLNode::XMLNodePtr newChild) throw (std::invalid_argument)
	{
		m_childs.push_back(newChild);
	}
}