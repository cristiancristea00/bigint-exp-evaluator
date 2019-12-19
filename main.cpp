#include <sstream>
#include <stack>
#include "BigInteger.h"
#include "Token.h"

void infixToPostfix(vector<Token>&);

int main()
{
    vector<Token> postfix;
    infixToPostfix(postfix);
    return 0;
}

void infixToPostfix(vector<Token>& queue)
{
    string expression;
    getline(cin, expression);
    istringstream exp(expression);

    stack<_Operator> ops;
    string token;
    _Operator op;

    while (exp >> token)
    {
        if ((token.size() > 1) || (token.size() == 1 && isdigit(token.at(0)))) //Verificam daca token-ul este operand
        {
            if (token.at(0) == '-')
            {
                token.erase(0, 1);
                queue.push_back({true, {MINUS, static_cast<unsigned int>(token.size()), token.c_str()}, false,});
                continue;
            }
            else if (token.at(0) == '+')
            {
                token.erase(0, 1);
                queue.push_back({true, {PLUS, static_cast<unsigned int>(token.size()), token.c_str()}, false,});
                continue;
            }
            else
            {
                queue.push_back({true, {PLUS, static_cast<unsigned int>(token.size()), token.c_str()}, false,});
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


    //Test
    for (auto x : queue)
    {
        if (x.isOperand)
        {
            cout << x.Operand << ' ';
        }
        else if (x.isOperator)
        {
            cout << x.Operator.sym << ' ';
        }
    }
}
