#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>

class RPN
{
    public:
        RPN();
        ~RPN();

        RPN(const RPN& other);
        RPN& operator=(const RPN& other);

        bool CalculateExpression(const std::string& expr, int& result);
    private:
        bool Calculate(const std::string& expr, int& result);
        bool IsOperator(const char c) const;
        bool PerformOperation(const int& first_operand, 
                              const int& second_operand, 
                              const char char_operator,
                              int& result);
        void CleanStack();
                    
        std::stack<int> numbers_;

};

#endif
