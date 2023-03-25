#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    (void)av;
    if (ac != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        exit(1);
    }
    std::map<std::string, double> _data = readData();
    // printMap(_data);
    checkInput(av[1], _data);
    return 0;
}