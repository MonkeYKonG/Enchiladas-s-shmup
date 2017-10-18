#include "MessagesException.hpp"

namespace	my
{
	static const std::string PrintClassErrorMessage(const std::string & functionPrototype)
	{
		return ("In function " + functionPrototype + ": ");
	}

	static const std::string PrintNumericVar(const std::string & varName, int value)
	{
		return (varName + " -> " + std::to_string(value));
	}

	const std::string MessagesException::NullPtr(const std::string & functionPrototype, const std::string & varName)
	{
		return (PrintClassErrorMessage(functionPrototype) + varName + " is a null pointer.");
	}

	const std::string MessagesException::InvalidIndex(const std::string & functionPrototype, const std::string & varName, int index)
	{
		return (PrintClassErrorMessage(functionPrototype) + PrintNumericVar(varName, index) + " is out of range.");
	}
}