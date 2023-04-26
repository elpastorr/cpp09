#include "PmergeMe.hpp"

bool    odd = false;
unsigned int    tmp;

void    pMergeMe(int ac, char **av)
{
    if ((ac - 1) % 2 != 0)
    {
        odd = true;

        if ((std::atoi(av[ac - 1])) < 0)
        {
            std::cerr << "Error: Negative number" << std::endl;
            exit(1);
        }
        tmp = std::atoi(av[ac - 1]);
    }
    ac--;
    std::cout << "Before:";
    if (ac < 6)
    {
        for (int i = 1; i < ac + 1; i++)
            std::cout << " " << av[i];
    }
    else
    {
        for (int i = 1; i < 5; i++)
            std::cout << " " << av[i];
        std::cout << " [...]";
    }
    std::cout << std::endl;

    std::vector<std::pair<unsigned int, unsigned int>> vec;
    for (int i = 1; i < ac; i += 2)
    {
        if (!checkNumber(av[i], av[i + 1]))
            exit(1);
        else
            vec.push_back(std::make_pair(std::atoi(av[i]), std::atoi(av[i + 1])));
    }
    std::vector<unsigned int> vec1, vec2;
    algo(ac, vec, vec1, vec2, true);

    std::deque<std::pair<unsigned int, unsigned int>> deq;
    for (int i = 1; i < ac; i += 2)
    {
        if (!checkNumber(av[i], av[i + 1]))
            exit(1);
        else
            deq.push_back(std::make_pair(std::atoi(av[i]), std::atoi(av[i + 1])));
    }
    std::deque<unsigned int> deq1, deq2;
    algo(ac, deq, deq1, deq2, false);
}

template <typename T, typename S, typename V>

void    algo(int ac, T &cont, S &cont1, V &cont2, bool opt)
{
    struct timeval start, end;
    long sec, micro;

    gettimeofday(&start, NULL);
    for (size_t i = 0; i < cont.size(); i++)
    {
        if (cont[i].first > cont[i].second)
            std::swap(cont[i].first, cont[i].second);
    }
    for (size_t i = 0; i < cont.size(); i++)
    {
        cont1.push_back(cont[i].first);
        cont2.push_back(cont[i].second);
    }
    std::sort(cont1.begin(), cont1.end());
    for (size_t i = 0; i < cont2.size(); i++)
        cont1.insert(std::lower_bound(cont1.begin(), cont1.end(), cont2[i]), cont2[i]);
    if (odd)
        cont1.insert(std::lower_bound(cont1.begin(), cont1.end(), tmp), tmp);
    gettimeofday(&end, NULL);
    sec = end.tv_sec - start.tv_sec;
    micro = end.tv_usec - start.tv_usec;
    long time = (sec / 1000000) + micro;
    if (opt == true)
    {
        std::cout << "After: (vector)";
        if (cont1.size() < 5)
        {
            for (size_t i = 0; i < cont1.size(); i++)
                std::cout << " " << cont1[i];
        }
        else
        {
            for (size_t i = 0; i < 4; i++)
                std::cout << " " << cont1[i];
            std::cout << " [...]";
        }
        std::cout << std::endl << "Time to process a range of " << ac << " elements with std::vector : " << time << " us" << std::endl;
    }
    else
    {
        std::cout << "After: (deque)";
        if (cont1.size() < 5)
        {
            for (size_t i = 0; i < cont1.size(); i++)
                std::cout << " " << cont1[i];
        }
        else
        {
            for (size_t i = 0; i < 4; i++)
                std::cout << " " << cont1[i];
            std::cout << " [...]";
        }
        std::cout << std::endl << "Time to process a range of " << ac << " elements with std::deque : " << time << " us" << std::endl;
    }
}

bool    checkNumber(char *nb1, char *nb2)
{
    for (int i = 0; nb1[i]; i++)
    {
        if (!isdigit(nb1[i]))
        {
            std::cerr << "Error: Invalid argument" << std::endl;
            return false;
        }
    }
    for (int i = 0; nb2[i]; i++)
    {
        if (!isdigit(nb2[i]))
        {
            std::cerr << "Error: Invalid argument" << std::endl;
            return false;
        }
    }
    if (std::atoi(nb1) < 0 || std::atoi(nb2) < 0)
    {
        std::cerr << "Error: Negative number" << std::endl;
        return false;
    }
    return true;
}
