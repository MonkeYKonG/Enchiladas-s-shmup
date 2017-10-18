#include "XMLNode.hpp"

namespace	my
{
	XMLNode::XMLNode(const ContentList & contents)
	{}

	XMLNodePtr XMLNode::create(const ContentList & contents)
	{
		return (XMLNodePtr(new XMLNode(contents)));
	}

	const XMLNode::NodeList &XMLNode::GetChilds() const
	{
		return (m_childs);
	}

	XMLNodePtr XMLNode::GetChild(int index) const
	{
		return (m_childs[index]);
	}

	XMLNodePtr XMLNode::GetChild(const std::string & key) const
	{
		for (unsigned i = 0; i < m_childs.size(); ++i)
			if (m_childs[i]->GetName() == key)
				return (m_childs[i]);
		return (XMLNodePtr(0));
	}

	const std::string &XMLNode::GetName() const
	{
		return (m_name);
	}

	const XMLNode::ContentList &XMLNode::GetContents() const
	{
		return (m_contents);
	}

	const XMLNode::NodeContent &XMLNode::GetContent(const std::string & key) const
	{
		for (unsigned i = 0; i < m_contents.size(); ++i)
			if (m_contents[i].first == key)
				return (m_contents[i]);
	}

	void XMLNode::AddChild(XMLNodePtr newChild)
	{
		m_childs.push_back(newChild);
	}
}