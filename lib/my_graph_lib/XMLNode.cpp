#include "XMLNode.hpp"

namespace	my
{
	XMLNode::XMLNode() noexcept
		: m_name("root")
	{}

	XMLNode::XMLNode(const std::string & name, const ContentList & contents) noexcept
		: m_name(name), m_contents(contents)
	{}

	XMLNode::XMLNodePtr XMLNode::create() noexcept
	{
		return (XMLNodePtr(new XMLNode()));
	}

	XMLNode::XMLNodePtr XMLNode::create(const std::string & name, const ContentList & contents) noexcept
	{
		return (XMLNodePtr(new XMLNode(name, contents)));
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

	const std::string &XMLNode::GetValue() const noexcept
	{
		return (m_value);
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

	void XMLNode::SetName(const std::string & name) noexcept
	{
		m_name = name;
	}

	void XMLNode::SetValue(const std::string & value) noexcept
	{
		m_value = value;
	}

	void XMLNode::AddAttribute(const XMLNode::NodeContent & attribute) noexcept
	{
		m_contents.push_back(attribute);
	}

	void XMLNode::AddAttributes(const XMLNode::ContentList & attributes) noexcept
	{
		for (unsigned i = 0; i < attributes.size(); ++i)
			m_contents.push_back(attributes[i]);
	}

	const std::string XMLNode::ToString() const noexcept
	{
		return (ToStringRec(""));
	}

	const std::string XMLNode::ToStringRec(const std::string & lineBegin) const noexcept
	{
		std::string str;

		str = lineBegin + "<" + m_name;
		for (unsigned i = 0; i < m_contents.size(); ++i)
			str += " " + m_contents[i].first + "=\"" + m_contents[i].second + "\"";
		str += ">\n";
		if (!m_value.empty())
			str += lineBegin + " " + m_value + "\n";
		for (unsigned i = 0; i < m_childs.size(); ++i)
			str += m_childs[i]->ToStringRec(lineBegin + " ") + "\n";
		str += lineBegin + "</" + m_name + ">";
		return (str);
	}
}