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

	const std::string MessagesException::NullPtr(const std::string & functionPrototype, const std::string & varName) noexcept
	{
		return (PrintClassErrorMessage(functionPrototype) + varName + " is a null pointer.");
	}

	const std::string MessagesException::InvalidIndex(const std::string & functionPrototype, const std::string & varName, int index) noexcept
	{
		return (PrintClassErrorMessage(functionPrototype) + PrintNumericVar(varName, index) + " is out of range.");
	}

	const std::string MessagesException::FileNotFound(const std::string & functionPrototype, const std::string &fileName) noexcept
	{
		return (PrintClassErrorMessage(functionPrototype) + fileName + " file not found.");
	}

	const std::string MessagesException::SyntaxError(const std::string & functionPrototype, const std::string & fileName, unsigned lineNum, unsigned charNum, const std::string & errorMessage, const std::string & expectedMessage)
	{
		return (PrintClassErrorMessage(functionPrototype) + "in file " + fileName + " line " + std::to_string(lineNum) + " character " + std::to_string(charNum) + ". Syntax error: " + errorMessage + ". Expected: " + expectedMessage);
	}
}