#pragma once

#include "XMLNode.hpp"

namespace	my
{
	class 	XMLParser
	{
	public:
		static XMLNodePtr Load(const std::string & fileName);

	private:
		XMLParser();
		~XMLParser();
	};
}