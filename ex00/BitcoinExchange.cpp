#include "BitcoinExchange.hpp"

std::map<std::string, double> readData()
{
    std::map<std::string, double> _data;
    std::ifstream file("data.csv");
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string date, rate;
        std::getline(ss, date, ',');
        std::getline(ss, rate);
        _data[date] = std::stod(rate);
    }
    return (_data);
}

void checkInput(char *input, std::map<std::string, double> data)
{
    std::ifstream file(input);
    if (!file)
    {
        std::cerr << "Error: could not open input file." << std::endl;
        exit(1);
    }
    std::string line;
    std::getline(file, line);
    if (line.compare("date | value"))
    {
        std::cerr << "Error: First line of input file is not 'date | value'." << std::endl;
        exit(1);
    }
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string date, value;
        char    separator;
        if (!(iss >> date >> separator >> value) || separator != '|')
            std::cout << "Error: bad input => " << line << std::endl;
        else if (!checkDate(date) || !checkValue(value))
            std::cout << "Error: bad input => " << line << std::endl;
        else if (stod(value) > 1000)
            std::cout << "Error: too large a number." << std::endl;
        else if (stod(value) < 0)
            std::cout << "Error: not a positive number." << std::endl;
        else
            std::cout << date << " => " << value << " = " << (stod(value) * getRate(date, data)) << std::endl;
    }
    file.close();
}

double  getRate(std::string date, std::map<std::string, double> data)
{
    std::map<std::string, double>::iterator it = data.find(date);
    if (it != data.end())
        return it->second;
    else
    {
        std::string previousDay = moveBackOneDay(date);
        if (!previousDay.compare("not valid date"))
            return 0;
        return getRate(previousDay, data);
    }
}

std::string moveBackOneDay(const std::string &date)
{
    int year, month, day;
    sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day);
    int prev_year = year, prev_month = month, prev_day = day - 1;
    if (prev_day == 0)
    {
        prev_month -= 1;
        if (prev_month == 0)
        {
            prev_month = 12;
            prev_year -= 1;
            if (prev_year < 2009)
                return "not valid date";
        }
        switch (prev_month)
        {
            case 2:
                if (prev_year % 4 == 0 && (prev_year % 100 != 0 || prev_year % 400 == 0))
                    prev_day = 29;
                else
                    prev_day = 28;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                prev_day = 30;
                break;
            default:
            prev_day = 31;
        }
    }
    std::string prev_date = std::to_string(prev_year) + '-';
    if (prev_month < 10)
        prev_date += "0" + std::to_string(prev_month);
    else
        prev_date += std::to_string(prev_month);
    if (prev_day < 10)
        prev_date += "-0" + std::to_string(prev_day);
    else
        prev_date += "-" + std::to_string(prev_day);
    return prev_date;
}

bool    checkDate(const std::string &date)
{
    if (date.length() != 10)
        return false;
    int year, month, day;
    char sep1, sep2;
    std::istringstream iss(date);
    iss >> year >> sep1 >> month >> sep2 >> day;
    if (iss.fail() || sep1 != '-' || sep2 != '-' || year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    bool leap_year = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if ((month == 2 && (leap_year ? day > 29 : day > 28)) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30))
        return false;
    return true;
}

bool    checkValue(const std::string &value)
{
    try
    {
        std::stof(value);
    }
    catch(const std::invalid_argument& e)
    {
        return false;
    }
    return true;
}

void printMap(const std::map<std::string, double>& map)
{
    std::map<std::string, double>::const_iterator it;
    for (it = map.begin(); it != map.end(); ++it)
        std::cout << it->first << "=" << it->second << " " << std::endl;
}
