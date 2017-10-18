#include "MessagesException.hpp"

namespace	my
{
	const std::string MessagesException::NullPtr(const std::string & functionName, const std::string & varName)
	{
		return (std::string("In function " + functionName + ": " + varName + " is a null pointer."));
	}
}