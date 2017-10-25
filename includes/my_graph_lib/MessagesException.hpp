#pragma once

#include <string>

namespace	my
{
	class 	MessagesException
	{
	public:
		static const std::string NullPtr(const std::string & functionPrototype, const std::string &varName) noexcept;
		static const std::string InvalidIndex(const std::string & functionPrototype, const std::string & varName, int value) noexcept;
		static const std::string FileNotFound(const std::string & functionPrototype, const std::string & fileName) noexcept;
		static const std::string SyntaxError(const std::string & functionPrototype, const std::string & fileName, unsigned lineNum, unsigned charNum, const std::string & errorMessage, const std::string & expectedMessage);

	private:
		MessagesException() noexcept {}
		~MessagesException() noexcept {}
	};
}