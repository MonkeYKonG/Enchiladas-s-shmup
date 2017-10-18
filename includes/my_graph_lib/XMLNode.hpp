#pragma once

#include <list>
#include <vector>
#include <memory>
#include <utility>

namespace my
{
	class XMLNode
	{
	public:
		typedef std::vector<std::shared_ptr<XMLNode> >	NodeList;
		typedef std::pair<std::string, std::string>  	NodeContent;
		typedef std::vector<NodeContent>			 	ContentList;

		~XMLNode();

		static std::shared_ptr<XMLNode> create(const ContentList & contents);

		const NodeList &GetChilds() const;
		std::shared_ptr<XMLNode> GetChild(int index) const;
		std::shared_ptr<XMLNode> GetChild(const std::string & key) const;
		const std::string &GetName() const;
		const ContentList &GetContents() const;
		const NodeContent &GetContent(const std::string & key) const;
		void AddChild(std::shared_ptr<XMLNode> newChild);
		
	private:
		XMLNode(const ContentList & contents);

		NodeList 	m_childs;
		std::string m_name;
		ContentList	m_contents;
	};

	typedef std::shared_ptr<XMLNode> XMLNodePtr;
}