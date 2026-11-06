#include "RPN.hpp"
#include <sstream>
#include <iostream>

static void LogErrorMsg(const std::string& token)
{
    std::cout << "Error: unexpected token '" << token << "'\n";
}

RPN::RPN()
{

}

RPN::~RPN()
{

}

RPN::RPN(const RPN& other) : numbers_(other.numbers_)
{}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
    {
        numbers_ = other.numbers_;
    }

    return *this;
}

bool RPN::CalculateExpression(const std::string& expr, int& result)
{
    bool calculation_was_successful = Calculate(expr, result);


    return calculation_was_successful;
}

bool RPN::Calculate(const std::string& expr, int& result)
{
    std::stringstream ss(expr);
    std::string token;

    while ((ss >> token))
    {
        if (token.size() != 1)
        {
            LogErrorMsg(token);
            return false;
        }

        if (IsOperator(token[0]))
        {
            if (numbers_.size() > 1)
            {
                int second_operand = numbers_.top();
                numbers_.pop();
                int first_operand = numbers_.top();
                numbers_.pop();
                
                int operation_result = 0;
                if (!PerformOperation(first_operand,
                                      second_operand,
                                      token[0],
                                      operation_result))
                {
                    // Log inside PerfomOperation
                    return false;
                }
                numbers_.push(operation_result);
            }
            else
            {
                LogErrorMsg(token);
                return false;
            }

        }
        else
        {
            if (!std::isdigit(static_cast<char>(token[0])))
            {
                LogErrorMsg(token);
                return false;
            }
            numbers_.push(token[0] - '0');
        }
    }
    if (numbers_.size() != 1)
    {
        std::cout << "Error: bad expression format\n";
        return false;
    }
    result = numbers_.top();

    return true;
}

bool RPN::IsOperator(const char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::PerformOperation(const int& first_operand, 
                        const int& second_operand, 
                        const char char_operator,
                        int& result)
{
    switch (char_operator)
    {
        case '+':
            result = first_operand + second_operand;
            break;
        case '-':
            result = first_operand - second_operand;
            break;
        case '*':
            result = first_operand * second_operand;
            break;
        case '/':
            if (second_operand == 0)
            {
                std::cout << "Error: can't divide by 0\n";
                return false;
            }
            result = first_operand / second_operand;
            break;
        default:
            return false;
    }
    
    return true;
}

void RPN::CleanStack()
{
    while (!numbers_.empty())
    {
        numbers_.pop();
    }
}
