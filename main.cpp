#include "BigInteger.h"
#include "Token.h"
#include <sstream>
#include <list>
#include <stack>

auto InfixToPostfix(std::string const & expression) noexcept -> std::list<Token>;
auto EvaluateInfix(std::list<Token> const & queue) noexcept -> BigInteger;

int main()
{
    std::string postfix;
    getline(std::cin, postfix);
    std::cout << EvaluateInfix(InfixToPostfix(postfix)) << '\n';
    return 0;
}

auto InfixToPostfix(std::string const & expression) noexcept -> std::list<Token>
{

    std::istringstream exp(expression);
    std::list<Token> queue;
    std::stack<Operator> ops;
    std::string token;
    Operator an_operator {};

    // For every element in the expression
    while (exp >> token)
    {
        // Verify if the token is an operand
        if ((token.size() > 1) || (token.size() == 1 && (isdigit(token.at(0)) != 0)))
        {
            if (token.at(0) == '-')
            {
                token.erase(0, 1);
                queue.push_back({true, {BigInteger::Sign::MINUS, static_cast<uint16_t>(token.size()), token.c_str()},
                                 false,});
                continue;
            }
            if (token.at(0) == '+')
            {
                token.erase(0, 1);
                queue.push_back({true, {BigInteger::Sign::PLUS, static_cast<uint16_t>(token.size()), token.c_str()},
                                 false,});
                continue;
            }
            queue.push_back({true, {BigInteger::Sign::PLUS, static_cast<uint16_t>(token.size()), token.c_str()},
                             false,});
            continue;
        }
        // The token is an operator or a  brace

        an_operator.sym = token.at(0);
        if (token.at(0) == '-' || token.at(0) == '+')
        {
            an_operator.pre = Precedence::ORD_1;
        }
        else if (token.at(0) == '*' || token.at(0) == '/')
        {
            an_operator.pre = Precedence::ORD_2;
        }
        else
        {
            an_operator.pre = Precedence::PAR;
        }

        if (an_operator.pre != Precedence::PAR)
        {
            while (!ops.empty() && ops.top().pre >= an_operator.pre && ops.top().sym != '(')
            {
                queue.push_back({false, {}, true, {ops.top().sym, ops.top().pre}});
                ops.pop();
            }
            ops.push(an_operator);
            continue;
        }
        if (an_operator.sym == '(')
        {
            ops.push(an_operator);
            continue;
        }
        if (an_operator.sym == ')')
        {
            while (!ops.empty() && ops.top().sym != '(')
            {
                queue.push_back({false, {}, true, {ops.top().sym, ops.top().pre}});
                ops.pop();
            }
            if (!ops.empty() && ops.top().sym == '(')
            {
                ops.pop();
            }
            continue;
        }
        break;
    }
    while (!ops.empty())
    {
        queue.push_back({false, {}, true, {ops.top().sym, ops.top().pre}});
        ops.pop();
    }
    return queue;
}

auto EvaluateInfix(std::list<Token> const & queue) noexcept -> BigInteger
{
    std::stack<Token> tokens;
    BigInteger first;
    BigInteger second;
    for (const auto & token: queue)
    {
        if (token.is_operator)
        {
            first = tokens.top().operand;
            tokens.pop();
            second = tokens.top().operand;
            tokens.pop();
            if (token.opt.sym == '+')
            {
                tokens.push({true, second + first, false, {}});
            }
            else if (token.opt.sym == '-')
            {
                tokens.push({true, second - first, false, {}});
            }
            else if (token.opt.sym == '*')
            {
                tokens.push({true, second * first, false, {}});
            }
            else if (token.opt.sym == '/')
            {
                tokens.push({true, second / first, false, {}});
            }
        }
        else if (token.is_operand)
        {
            tokens.push(token);
        }
    }
    return tokens.top().operand;
}
