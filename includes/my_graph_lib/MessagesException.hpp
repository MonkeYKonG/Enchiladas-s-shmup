#pragma once

#include <string>

namespace	my
{
	class 	MessagesException
	{
	public:
		static const std::string NullPtr(const std::string & functionName, const std::string &varName);

	private:
		MessagesException() {}
		~MessagesException() {}
	};
}