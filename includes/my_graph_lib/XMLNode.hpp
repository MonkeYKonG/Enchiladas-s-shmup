#pragma once

#include <list>
#include <memory>

namespace my
{
	class XMLNode
	{
	public:
		typedef std::list<std::shared_ptr<XMLNode> > NodeList;
		typedef std::paire<std::string, std::string> NodeContent;
		typedef std::vector<NodeContent>			 NodeList;

		~XMLNode();

		const NodeList &GetChilds() const;
		XMLNodePtr GetChild(int index) const;
		XMLNodePtr GetChild(const std::string & key) const;
		const NodeList &GetContents() const;
		const NodeContent &GetContent(const std::string & key);
		void AddChild(XMLNodePtr newChild);
		void RemoveChild(int index);
		void RemoveChild(const std::string & key);
		
	private:
		XMLNode();

		NodeList 	m_childs;
		std::string m_name;
		NodeList	m_contents;
	};

	typedef std::shared_ptr<XMLNode> XMLNodePtr;
}