#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <sys/time.h>
# include <algorithm>
#include <unistd.h>

void    pMergeMe(int ac, char **av);
template <typename T, typename S, typename V>
void    algo(int ac, T &cont, S &cont1, V &cont2, bool opt);
bool    checkNumber(char *nb1, char *nb2);

#endif