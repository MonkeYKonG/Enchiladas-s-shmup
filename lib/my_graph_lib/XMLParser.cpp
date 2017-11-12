#include <fstream>
#include <cctype>
#include "XMLParser.hpp"
#include "MessagesException.hpp"

#include <iostream>

namespace	my
{
	const char XMLParser::BEACON_CONSTANTS_DELIM_BEGIN[XMLParser::BEACON_CONSTANTS_DELIM_SIZE + 1] = "$(";
	const char XMLParser::BEACON_CONSTANTS_DELIM_END[XMLParser::BEACON_CONSTANTS_DELIM_SIZE + 1] = ")$";
	XMLParser::CONSTANTS XMLParser::XML_CONSTANTS = XMLParser::CONSTANTS();
#ifdef __linix__
	const std::string XMLParser::XML_RESOURCES_PATH = "resources/xmls/";
#elif _WIN32
	const std::string XMLParser::XML_RESOURCES_PATH = "../../../resources/xmls/";
#endif

	XMLParser::XMLParser(std::ifstream & fs, const std::string & fileName) noexcept
		: m_fs(fs), m_fileName(fileName), m_index(0)
	{}

	void	XMLParser::TranslateConstants(std::string & value) throw (std::invalid_argument)
	{
		unsigned ndx = 0;
		unsigned begin, end, delimNdx;
		std::string stk;

		while ((begin = value.find(BEACON_CONSTANTS_DELIM_BEGIN, ndx)) != static_cast<unsigned>(std::string::npos) && (end = value.find(BEACON_CONSTANTS_DELIM_END, begin + BEACON_CONSTANTS_DELIM_SIZE)) != static_cast<unsigned>(std::string::npos))
		{
			ndx = begin + BEACON_CONSTANTS_DELIM_SIZE;
			stk = value.substr(ndx, end - ndx);
			if ((delimNdx = stk.find('.')) == std::string::npos)
				throw (std::invalid_argument("XMLParser: TranslateConstants: syntax error no demlimiter"));
			try
			{
				value = value.substr(0, begin) + XML_CONSTANTS.at(stk.substr(0, delimNdx)).at(stk.substr(delimNdx + 1)) + value.substr(end + BEACON_CONSTANTS_DELIM_SIZE);
			}
			catch (const std::out_of_range & e)
			{
				throw (e);
			}
			ndx = end + BEACON_CONSTANTS_DELIM_SIZE;
		}
	}

	void	XMLParser::EvaluateOperation(std::string & value) throw (std::invalid_argument)
	{
		// get string then call recusive function to convert operation into number
	}

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
		try
		{
			TranslateConstants(nextValue);
			EvaluateOperation(nextValue);
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
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

	void XMLParser::AddConstants() throw (std::invalid_argument)
	{
		std::string name;
		XMLNode::ContentList args;
		unsigned beaconEnd;

		try
		{
			while (m_fileContent[m_index] == BEACON_BEGIN && m_fileContent[m_index + 1] == BEACON_CONSTANT)
			{
				m_index += 2;
				JumpSpace();
				if ((beaconEnd = m_fileContent.find(BEACON_CONSTANT, m_index)) == std::string::npos || m_fileContent[beaconEnd + 1] != BEACON_END)
					throw (std::invalid_argument("syntax error: invalid beacon ending"));
				name = GetNextWord();
				while (m_index < beaconEnd)
					args.push_back(GetNextArg());
				m_index += 2;
				JumpSpace();
				if (name.empty() || args.empty())
					throw (std::invalid_argument("XMLParser: AddConstants: empty node"));
				if (XML_CONSTANTS.find(name) == XML_CONSTANTS.end())
				{
					XML_CONSTANTS[name] = CONSTANT();
					for (unsigned i = 0; i < args.size(); ++i)
					{
						if (XML_CONSTANTS.at(name).find(args[i].first) == XML_CONSTANTS.at(name).end())
							XML_CONSTANTS.at(name)[args[i].first] = args[i].second;
						else
							throw (std::invalid_argument("XMLParser: AddConstants: " + name + "." + args[i].first + " already exist"));
					}
				}
				else
					throw (std::invalid_argument("XMLParser: AddContents: " + name + " already exist"));
			}
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
	}

	XMLNode::XMLNodePtr XMLParser::CheckLink() throw (std::invalid_argument)
	{
		unsigned beaconEnd;
		std::string fileName;

		try
		{
			if (m_fileContent[m_index] == BEACON_BEGIN && m_fileContent[m_index + 1] == BEACON_LINK)
			{
				m_index += 2;
				JumpSpace();
				if ((beaconEnd = m_fileContent.find(BEACON_LINK, m_index)) == std::string::npos || m_fileContent[beaconEnd + 1] != BEACON_END)
					throw (std::invalid_argument("XMLParser: CheckLink: invalid beacon ending"));
				fileName = m_fileContent.substr(m_index, beaconEnd - m_index);
				while (std::isspace(fileName.back()))
					fileName.pop_back();
				m_index = beaconEnd + 2;
				JumpSpace();
				return (XMLParser::Load(fileName));
			}
		}
		catch (const std::invalid_argument & e)
		{
			throw (e);
		}
		return (0);
	}

	XMLNode::XMLNodePtr XMLParser::Parse() throw (std::invalid_argument)
	{
		if (!std::getline(m_fs, m_fileContent, static_cast<char>(4)))
			throw (std::invalid_argument("can't read file file."));
		m_fs.close();
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
		try
		{
			AddConstants();
			if ((node = CheckLink()))
				return (node);
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
		std::ifstream fs(XML_RESOURCES_PATH + fileName);
		XMLParser parser(fs, fileName);

		if (!fs)
			throw (std::invalid_argument(MessagesException::FileNotFound("XMLParser::Load(const std::string & fileName)", fileName)));
		return (parser.Parse());
	}
}