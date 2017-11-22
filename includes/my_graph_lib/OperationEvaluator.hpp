#pragma once

#include <stdexcept>
#include <vector>
#include <cctype>
#include <algorithm>

namespace my
{
	template <typename T>
	class OperationEvaluator
	{
	public:
		static T ParseOperation(const std::string & operation) throw (std::invalid_argument);

	private:
		struct Operation
		{
			std::vector<T> operands;
			std::vector<char> operators;
		};

		static const char PARENTHESES_OPEN = '(';
		static const char PARENTHESES_CLOSE = ')';
		static const std::string OPERATORS;

		static void JumpSpace(const std::string & str, unsigned & ndx) noexcept;
		static T GetValue(const std::string & str, unsigned & ndx) throw (std::invalid_argument);
		static T EvaluateParentheses(const std::string & str, unsigned & ndx) throw (std::invalid_argument);
		static char GetOperator(const std::string & str, unsigned & ndx) throw (std::invalid_argument);
		static unsigned NextPrioOpp(const std::vector<char> & operators) noexcept;
		static T Solve(T opp1, T opp2, char oper) throw (std::invalid_argument);

		OperationEvaluator() {}
		~OperationEvaluator() {}
	};
}

template<typename T>
const std::string my::OperationEvaluator<T>::OPERATORS = "+-*/%";

template<typename T>
void my::OperationEvaluator<T>::JumpSpace(const std::string & str, unsigned & ndx) noexcept
{
	while (std::isspace(str[ndx]))
		ndx++;
}

template<typename T>
T my::OperationEvaluator<T>::GetValue(const std::string & str, unsigned & ndx) throw (std::invalid_argument)
{
	unsigned stkNdx;

	if (str[ndx] == PARENTHESES_OPEN)
		return (EvaluateParentheses(str, ndx));
	stkNdx = ndx;
	while (ndx < str.size() && !std::isspace(str[ndx]))
		ndx++;
	JumpSpace(str, ndx);
	return std::stof(&str[stkNdx]);
}

template<typename T>
T my::OperationEvaluator<T>::EvaluateParentheses(const std::string & str, unsigned & ndx) throw (std::invalid_argument)
{
	unsigned openParentheses = 1;
	unsigned begin = ndx + 1;
	unsigned end;

	while (openParentheses)
	{
		if (++ndx >= str.size())
			throw (std::invalid_argument("OperationEvaluator: GetValue: can't find closing parentheses"));
		if (str[ndx] == PARENTHESES_OPEN)
			openParentheses++;
		else if (str[ndx] == PARENTHESES_CLOSE)
			openParentheses--;
	}
	end = ndx;
	ndx++;
	JumpSpace(str, ndx);
	return (ParseOperation(str.substr(begin, end - begin)));
}

template<typename T>
char my::OperationEvaluator<T>::GetOperator(const std::string & operation, unsigned & ndx) throw (std::invalid_argument)
{
	unsigned operatorNdx;

	if ((operatorNdx = OPERATORS.find(operation[ndx])) == static_cast<unsigned>(std::string::npos))
		throw (std::invalid_argument("OperationEvaluator: GetOperator: unknow operator"));
	ndx++;
	JumpSpace(operation, ndx);
	return OPERATORS[operatorNdx];
}

template<typename T>
unsigned my::OperationEvaluator<T>::NextPrioOpp(const std::vector<char> & operators) noexcept
{
	for (unsigned i = 0; i < operators.size(); ++i)
	{
		if (operators[i] == '*' || operators[i] == '/' || operators[i] == '%')
			return (i);
	}
	return (0);
}

template<typename T>
T my::OperationEvaluator<T>::Solve(T opp1, T opp2, char oper) throw (std::invalid_argument)
{
	switch (oper)
	{
	case '+':
		return (opp1 + opp2);

	case '-':
		return (opp1 - opp2);

	case '*':
		return (opp1 * opp2);

	case '/':
		return (opp1 / opp2);

	case '%':
		return (opp1 % opp2);
	}
	throw (std::invalid_argument("OperationEvaluator: Solve: unknow operator"));
}

template<typename T>
T my::OperationEvaluator<T>::ParseOperation(const std::string & operation) throw (std::invalid_argument)
{
	Operation opp;
	unsigned ndx = 0;

	try
	{
		JumpSpace(operation, ndx);
		while (ndx < operation.size())
		{
			opp.operands.push_back(GetValue(operation, ndx));
			if (ndx < operation.size())
				opp.operators.push_back(GetOperator(operation, ndx));
		}
		while (!opp.operators.empty())
		{
			ndx = NextPrioOpp(opp.operators);
			opp.operands[ndx] = Solve(opp.operands[ndx], opp.operands[ndx + 1], opp.operators[ndx]);
			opp.operands.erase(std::find(opp.operands.begin(), opp.operands.end(), opp.operands[ndx + 1]));
			opp.operators.erase(std::find(opp.operators.begin(), opp.operators.end(), opp.operators[ndx]));
		}
	}
	catch (const std::invalid_argument & e)
	{
		throw (e);
	}
	return (opp.operands[0]);
}
