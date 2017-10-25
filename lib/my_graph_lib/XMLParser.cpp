#include <fstream>
#include <cctype>
#include "XMLParser.hpp"
#include "MessagesException.hpp"

#include <iostream>

namespace	my
{
	XMLParser::XMLParser(std::ifstream & fs, const std::string & fileName) noexcept
		: m_fs(fs), m_fileName(fileName), m_index(0)
	{}	

	void XMLParser::JumpSpace() noexcept
	{
		while (m_index < m_fileContent.size() && std::isspace(m_fileContent[m_index]))
			m_index++;
	}
	
	const std::string XMLParser::GetNextWord() throw (std::invalid_argument)
	{
		std::string nextWord;

		while (m_index < m_fileContent.size() && std::isalnum(m_fileContent[m_index]))
		{
			nextWord += m_fileContent[m_index];
			m_index++;
		}
		if (nextWord.empty())
			throw (std::invalid_argument("syntax error unexpedted char"));
		JumpSpace();
		//std::cout << "get next word: " << nextWord << std::endl;
		//std::cout << "index: " << m_index << " " << m_fileContent[m_index] << std::endl;
		return (nextWord);
	}

	const std::string XMLParser::GetNextString() throw (std::invalid_argument)
	{
		std::string nextString;

		if (m_fileContent[m_index] != BEACON_STR_DELIM)
			throw (std::invalid_argument("syntax error unexpected char"));
		m_index++;
		while (m_index < m_fileContent.size() && m_fileContent[m_index] != BEACON_STR_DELIM)
		{
			nextString += m_fileContent[m_index];
			m_index++;
		}
		if (m_index >= m_fileContent.size())
			throw (std::invalid_argument("Syntax error unexpedted char"));
		m_index++;
		JumpSpace();
		//std::cout << "next string: " << nextString << std::endl;
		return (nextString);
	}

	const std::string XMLParser::GetNextValue() throw (std::invalid_argument)
	{
		std::string nextValue;

		while (m_index < m_fileContent.size() && m_fileContent[m_index] != BEACON_BEGIN)
		{
			while (!std::isspace(m_fileContent[m_index]) && m_fileContent[m_index] != BEACON_BEGIN)
				nextValue += m_fileContent[m_index++];
			nextValue += " ";
			JumpSpace();
		}
		if (m_index >= m_fileContent.size())
			throw (std::invalid_argument("Syntax error end of string"));
		if (nextValue.empty())
			throw (std::invalid_argument("Syntax error empty node value"));
		while (std::isspace(nextValue.back()))
			nextValue.pop_back();
		//std::cout << "next value: " << nextValue << std::endl;
		return (nextValue);
	}

	const XMLNode::NodeContent XMLParser::GetNextArg() throw (std::invalid_argument)
	{
		XMLNode::NodeContent arg;

		try
		{
			arg.first = GetNextWord();
			if (m_fileContent[m_index] != BEACON_ATTRIBUTE)
				throw (std::invalid_argument("Syntax error unexpedted character"));
			m_index++;
			JumpSpace();
			arg.second = GetNextString();
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (arg);
	}

	void XMLParser::GetBeaconContent(std::string & name, XMLNode::ContentList & args) throw (std::invalid_argument)
	{
		unsigned beaconEnd;
		
		if (m_fileContent[m_index] != BEACON_BEGIN)
			throw (std::invalid_argument("syntax error: invalid beacon opening"));
		if ((beaconEnd = m_fileContent.find(BEACON_END, m_index)) == std::string::npos)
			throw (std::invalid_argument("Syntax error: miss beacon ending"));
		//std::cout << "beacon content: " << m_fileContent.substr(m_index, beaconEnd - m_index + 1) << std::endl;
		m_index ++;
		JumpSpace();
		try
		{
			name = GetNextWord();
			while (m_index < beaconEnd)
				args.push_back(GetNextArg());
		}	
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		m_index++;
		JumpSpace();
	}

	XMLNode::XMLNodePtr XMLParser::Parse() throw (std::invalid_argument)
	{
		if (!std::getline(m_fs, m_fileContent, static_cast<char>(4)))
			throw (std::invalid_argument("can't read file file."));
		try
		{
			return (ParseRec());
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
	}

	XMLNode::XMLNodePtr XMLParser::ParseRec() throw (std::invalid_argument)
	{
		std::string name;
		XMLNode::ContentList args;
		XMLNode::XMLNodePtr node;

		JumpSpace();
		//std::cout << m_fileContent.substr(m_index) << std::endl;
		try
		{
			GetBeaconContent(name, args);
			node = XMLNode::create(name, args);
			m_beacons.push(name);
			if (m_fileContent[m_index] == BEACON_BEGIN)
			{
				while (m_fileContent[m_index] == BEACON_BEGIN)
				{
					if (m_fileContent[m_index + 1] == BEACON_CLOSE)
					{
						m_index += 2;
						JumpSpace();
						if (m_beacons.empty() || GetNextWord() != m_beacons.top())
							throw (std::invalid_argument("Syntax error wrong closing beacong"));
						if (m_fileContent[m_index] != BEACON_END)
							throw (std::invalid_argument("Syntax error unexpedted char"));
						m_beacons.pop();
						m_index++;
						JumpSpace();
						return (node);
					}
					else
						node->AddChild(ParseRec());
				}
			}
			else
			{
				node->SetValue(GetNextValue());
				if (m_fileContent[m_index] != BEACON_BEGIN || m_fileContent[m_index + 1] != BEACON_CLOSE)
					throw (std::invalid_argument("Syntax error unexpedted char"));
				m_index += 2;
				JumpSpace();
				if (m_beacons.empty() || GetNextWord() != m_beacons.top())
					throw (std::invalid_argument("Syntax error wrong closing beacong"));
				if (m_fileContent[m_index] != BEACON_END)
					throw (std::invalid_argument("Syntax error unexpedted char"));
				m_beacons.pop();
				m_index++;
				JumpSpace();
				return (node);
			}
		}
		catch (std::invalid_argument & e)
		{
			throw (e);
		}
		return (0);
	}

	XMLNode::XMLNodePtr	XMLParser::Load(const std::string &fileName) throw (std::invalid_argument)
	{
		std::ifstream fs(fileName);
		XMLParser parser(fs, fileName);

		if (!fs)
			throw (std::invalid_argument(MessagesException::FileNotFound("XMLParser::Load(const std::string & fileName)", fileName)));
		return (parser.Parse());
	}
}