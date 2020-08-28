#include "BigInteger.h"
#include "Token.h"
#include <sstream>
#include <list>
#include <stack>

list<Token> InfixToPostfix(string const&) noexcept;
BigInteger EvaluateInfix(list<Token> const&) noexcept;

int main()
{
    string postfix;
    getline(cin, postfix);
    cout << EvaluateInfix(InfixToPostfix(postfix)) << '\n';
    return 0;
}

list<Token> InfixToPostfix(string const& expression) noexcept
{

    istringstream exp(expression);
    list<Token> queue;
    stack<Operator> ops;
    string token;
    Operator op{};

    // For every element in the expression
    while (exp >> token)
    {
        // Verify if the token is an operand
        if ((token.size() > 1) || (token.size() == 1 && isdigit(token.at(0))))
        {
            if (token.at(0) == '-')
            {
                token.erase(0, 1);
                queue.push_back({true, {MINUS, static_cast<short unsigned>(token.size()), token.c_str()}, false,});
                continue;
            }
            else if (token.at(0) == '+')
            {
                token.erase(0, 1);
                queue.push_back({true, {PLUS, static_cast<short unsigned>(token.size()), token.c_str()}, false,});
                continue;
            }
            else
            {
                queue.push_back({true, {PLUS, static_cast<short unsigned>(token.size()), token.c_str()}, false,});
                continue;
            }
        }
            // The token is an operator or a  brace
        else
        {
            op.sym = token.at(0);
            if (token.at(0) == '-' || token.at(0) == '+')
            {
                op.pre = ORD_1;
            }
            else if (token.at(0) == '*' || token.at(0) == '/')
            {
                op.pre = ORD_2;
            }
            else
            {
                op.pre = PAR;
            }
        }

        if (op.pre != PAR)
        {
            while (!ops.empty() && ops.top().pre >= op.pre && ops.top().sym != '(')
            {
                queue.push_back({false, {}, true, {ops.top().sym, ops.top().pre}});
                ops.pop();
            }
            ops.push(op);
            continue;
        }
        else if (op.sym == '(')
        {
            ops.push(op);
            continue;
        }
        else if (op.sym == ')')
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

BigInteger EvaluateInfix(list<Token> const& queue) noexcept
{
    stack<Token> tokens;
    BigInteger a, b;
    for (const auto& tk : queue)
    {
        if (tk.is_operator)
        {
            a = tokens.top().operand;
            tokens.pop();
            b = tokens.top().operand;
            tokens.pop();
            if (tk._operator.sym == '+')
            {
                tokens.push({true, b + a, false, {}});
            }
            else if (tk._operator.sym == '-')
            {
                tokens.push({true, b - a, false, {}});
            }
            else if (tk._operator.sym == '*')
            {
                tokens.push({true, b * a, false, {}});
            }
            else if (tk._operator.sym == '/')
            {
                tokens.push({true, b / a, false, {}});
            }
        }
        else if (tk.is_operand)
        {
            tokens.push(tk);
        }
    }
    return tokens.top().operand;
}