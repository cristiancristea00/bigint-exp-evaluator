#include "BigInteger.h"
#include "Token.h"
#include <sstream>
#include <vector>
#include <stack>

vector<Token> infixToPostfix(const string&);
BigInteger evaluateInfix(const vector<Token>&);

int main()
{
    string postfix;
    getline(cin, postfix);
    cout << evaluateInfix(infixToPostfix(postfix)) << '\n';
    return 0;
}

vector<Token> infixToPostfix(const string& expression)
{

    istringstream exp(expression);
    vector<Token> queue;
    stack<_Operator> ops;
    string token;
    _Operator op{};

    while (exp >> token) //Pentru fiecare element din expresie
    {
        if ((token.size() > 1) || (token.size() == 1 && isdigit(token.at(0)))) //Verificam daca token-ul este operand
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
        else //Token-ul este operator sau paranteza
        {
            op.sym = token.at(0);
            if (token.at(0) == '-' || token.at(0) == '+')
            {
                op.pre = ORD1;
            }
            else if (token.at(0) == '*' || token.at(0) == '/')
            {
                op.pre = ORD2;
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

BigInteger evaluateInfix(const vector<Token>& queue)
{
    stack<Token> tokens;
    BigInteger a, b;
    for (auto tk : queue)
    {
        if (tk.isOperator)
        {
            a = tokens.top().Operand;
            tokens.pop();
            b = tokens.top().Operand;
            tokens.pop();
            if (tk.Operator.sym == '+')
            {
                tokens.push({true, b + a, false, {}});
            }
            else if (tk.Operator.sym == '-')
            {
                tokens.push({true, b - a, false, {}});
            }
            else if (tk.Operator.sym == '*')
            {
                tokens.push({true, b * a, false, {}});
            }
            else if (tk.Operator.sym == '/')
            {
                tokens.push({true, b / a, false, {}});
            }
        }
        else if (tk.isOperand)
        {
            tokens.push(tk);
        }
    }
    return tokens.top().Operand;
}