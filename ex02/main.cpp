#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error" << std::endl;
        exit(1);
    }
    else
        pMergeMe(ac, av);
}
