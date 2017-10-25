#pragma once

#include <list>
#include <vector>
#include <memory>
#include <utility>
#include <stdexcept>

namespace my
{
	class XMLNode
	{
	public:
		typedef std::vector<std::shared_ptr<XMLNode> >	NodeList;
		typedef std::pair<std::string, std::string>  	NodeContent;
		typedef std::vector<NodeContent>			 	ContentList;
		typedef std::shared_ptr<XMLNode> XMLNodePtr;

		~XMLNode() noexcept {}

		static XMLNodePtr create() noexcept;
		static XMLNodePtr create(const std::string & name, const ContentList & contents) noexcept;

		const NodeList &GetChilds() const noexcept;
		XMLNodePtr GetChild(int index) const throw (std::out_of_range);
		XMLNodePtr GetChild(const std::string & key) const throw (std::out_of_range);
		const std::string &GetName() const noexcept;
		const std::string &GetValue() const noexcept;
		const ContentList &GetContents() const noexcept;
		const NodeContent &GetContent(const std::string & key) const throw (std::out_of_range);
		void AddChild(XMLNodePtr newChild) throw (std::invalid_argument);
		void SetName(const std::string & name) noexcept;
		void SetValue(const std::string & value) noexcept;
		void AddAttribute(const NodeContent & attribute) noexcept;
		void AddAttributes(const ContentList & contents) noexcept;
		const std::string ToString() const noexcept;
		
	private:
		XMLNode() noexcept;
		XMLNode(const std::string & name, const ContentList & contents) noexcept;

		const std::string ToStringRec(const std::string & lineBegin) const noexcept;

		NodeList 	m_childs;
		std::string m_name;
		ContentList	m_contents;
		std::string	m_value;
	};
}