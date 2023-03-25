#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

std::map<std::string, double> readData();
void checkInput(char *input, std::map<std::string, double> data);
double  getRate(std::string date, std::map<std::string, double> data);
std::string moveBackOneDay(const std::string &date);
bool    checkDate(const std::string &date);
bool    checkValue(const std::string &value);


void printMap(const std::map<std::string, double>& map);

#endif