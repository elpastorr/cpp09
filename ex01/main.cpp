#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: Wrong number of arguments" << std::endl;
        exit(1);
    }
    try
    {
        read_RPN(av[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what();
    }
}
