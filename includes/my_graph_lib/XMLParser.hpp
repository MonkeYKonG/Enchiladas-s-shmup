#pragma once

#include <stack>
#include "XMLNode.hpp"

namespace	my
{
	class 	XMLParser
	{
	public:
		~XMLParser() noexcept {}

		static XMLNode::XMLNodePtr Load(const std::string & fileName) throw (std::invalid_argument);
		XMLNode::XMLNodePtr Parse() throw (std::invalid_argument);

	private:
		static const char BEACON_BEGIN = '<';
		static const char BEACON_END = '>';
		static const char BEACON_CLOSE = '/';
		static const char BEACON_COMMENT = '#';
		static const char BEACON_ATTRIBUTE = '=';
		static const char BEACON_STR_DELIM = '"';

		XMLParser(std::ifstream & m_fs, const std::string & fileName) noexcept;
		void JumpSpace() noexcept;
		const std::string GetNextWord() throw (std::invalid_argument);
		const std::string GetNextString() throw (std::invalid_argument);
		const std::string GetNextValue() throw (std::invalid_argument);
		const XMLNode::NodeContent GetNextArg() throw (std::invalid_argument);
		void GetBeaconContent(std::string & name, XMLNode::ContentList & args) throw (std::invalid_argument);
		XMLNode::XMLNodePtr ParseRec() throw (std::invalid_argument);

		std::ifstream			&m_fs;
		std::stack<std::string>	m_beacons;
		const std::string		&m_fileName;
		std::string				m_fileContent;
		unsigned 				m_index;
	};
}