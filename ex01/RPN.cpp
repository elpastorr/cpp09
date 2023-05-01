#include "RPN.hpp"

int calcul(int n1, int n2, char o)
{
    switch (o)
    {
        case '+':
            return (n1 + n2);
        case '-':
            return (n1 - n2);
        case '*':
            return (n1 * n2);
        case '/':
        {
            if (n2 == 0)
                throw std::invalid_argument("Division by 0 imposible.");
            return (n1 / n2);
        }
    }
    return (0);
}

void    read_RPN(std::string input)
{
    std::stack<int> nbrs;
    std::string ops = "+-*/";
    int op, num;
    op = num = 0;
    for (size_t i = 0; i < input.length(); i++)
    {
        if (input[i] >= '0' && input[i] <= '9')
        {
            if (input[i + 1] && (input[i + 1] != ' '))
                throw std::invalid_argument("Invalid Input");
            num++;
            nbrs.push(input[i] - '0');
        }
        else if (nbrs.size() == 0)
        {
            break;
        }
        else if (ops.find(input[i]) != std::string::npos)
        {
            if (num < 2 || (input[i + 1] && (input[i + 1] != ' ')))
                throw std::invalid_argument("Invalid Input");
            op++;
            int n2 = nbrs.top();
            nbrs.pop(); 
            if (nbrs.size() != 0)
                nbrs.top() = calcul(nbrs.top(), n2, input[i]);
        }
        else if (input[i] != ' ')
            throw std::invalid_argument("Invalid Input");
    }
    if (num != (op + 1))
        throw std::invalid_argument("Number of operator invalid.");
    std::cout << nbrs.top() << std::endl;
}