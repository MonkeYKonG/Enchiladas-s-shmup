#pragma once

#include <string>

namespace	my
{
	class 	MessagesException
	{
	public:
		static const std::string NullPtr(const std::string & functionPrototype, const std::string &varName);
		static const std::string InvalidIndex(const std::string & functionPrototype, const std::string &varName, int value);

	private:
		MessagesException() {}
		~MessagesException() {}
	};
}