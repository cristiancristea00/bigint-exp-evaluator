enum class Precedence
{
    PAR,
    ORD_1,
    ORD_2,
};

struct Operator
{
    char sym;
    Precedence pre;
};

struct Token
{
    bool is_operand = false;
    BigInteger operand = {};
    bool is_operator = false;
    Operator opt = {};
};
