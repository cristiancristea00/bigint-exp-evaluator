enum PRECEDENCE
{
    PAR,
    ORD1,
    ORD2,
};

struct _Operator
{
    char sym;
    PRECEDENCE pre;
};

struct Token
{
    bool isOperand = false;
    BigInteger Operand = {};
    bool isOperator = false;
    _Operator Operator;
};