/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:50:36 by ael-maar          #+#    #+#             */
/*   Updated: 2023/11/21 10:37:38 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
    std::string line;
    try
    {
        std::ifstream data_read("../cpp_09/data.csv");
        if (!data_read.is_open())
        {
            std::cerr << "Error: " << strerror(errno) << std::endl;
            exit(EXIT_FAILURE);
        }
        std::getline(data_read, line); // skip the first line
        while (std::getline(data_read, line))
        {
            size_t separator = line.find(",");
            btc_data[strToTimestamp(line.substr(0, separator))] = strToDouble(line.substr(separator + 1));
        }
        data_read.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        throw;
    }
    
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src) { *this = src; }

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &src)
{
    if (this != &src)
        this->btc_data = src.btc_data;
    return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

time_t BitcoinExchange::strToTimestamp(const std::string &dateString) const
{
    std::tm tm = {};
    std::istringstream date_stream(dateString);
    date_stream >> tm.tm_year;
    date_stream.ignore(1); // Ignore the '-' separator
    date_stream >> tm.tm_mon;
    date_stream.ignore(1); // Ignore the '-' separator
    date_stream >> tm.tm_mday;

    tm.tm_year -= 1900; // Adjust year to be years since 1900
    tm.tm_mon -= 1;    // Adjust month to be in the range 0-11

    return (std::mktime(&tm));
}

bool BitcoinExchange::AboveCurrentDate(int year, int month, int day) const
{
    std::time_t currentTime;
    std::time(&currentTime);

    std::tm* timeInfo = std::localtime(&currentTime);

    int currentYear = timeInfo->tm_year + 1900;
    int currentMonth = timeInfo->tm_mon + 1;
    int currentDay = timeInfo->tm_mday;
    
    if (year > currentYear)
        return (true);
    else if (year == currentYear && month > currentMonth)
        return (true);
    else if (year == currentYear && month == currentMonth && day > currentDay)
        return (true);
    return (false);
}

bool BitcoinExchange::parseDate(const std::string &input, int &year, int &month, int &day) const
{
    std::string year_str, month_str, day_str;

    year_str = input.substr(0,4);
    month_str = input.substr(5,2);
    day_str = input.substr(8,2);

    if (!isNumeric(year_str) || !isNumeric(month_str) || !isNumeric(day_str))
        return (false);
    year = atoi(year_str.c_str());
    month = atoi(month_str.c_str());
    day = atoi(day_str.c_str());
    if (year < 1900 || month < 1 || month > 12 || day > 31)
        return (false);
    int maxDay = 31;
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDay = 30;
    } else if (month == 2) // handle February with leap year
        maxDay = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
    if (day < 1 || day > maxDay)
        return (false);
    if (AboveCurrentDate(year, month, day))
        return (false);
    return (true);
}


bool BitcoinExchange::isValidInputDate(const std::string &input_date) const
{
    int year, month, day;

    if (input_date.length() != 11)
        return (false);
    if (input_date[4] != '-' || input_date[7] != '-' || input_date[10] != ' ')
        return (false);
    if (!parseDate(input_date, year, month, day))
        return (false);
    return (true);
}

bool BitcoinExchange::isDecimalNumber(const std::string& str) const
{
    char* end;
    std::strtod(str.c_str(), &end);

    return end == (str.c_str() + str.length());
}

bool BitcoinExchange::isValidInputValue(const std::string &input_value) const
{
    if (!std::isspace(input_value[0]) || std::isspace(input_value[1]))
        return (false);
    if (!isDecimalNumber(input_value))
        return (false);
    return (true);
}

bool BitcoinExchange::valueConstraints(const std::string &input_value, double &value) const
{
    value = strToDouble(input_value);
    if (value < 0)
    {
        std::cerr << "Error: not a positive number" << std::endl;
        return (false);
    }
    if (value > 1000)
    {
        std::cerr << "Error: too large number" << std::endl;
        return (false);
    }
    return (true);
}

bool BitcoinExchange::searchAndCalculate(const std::string &input_date, double value) const
{
    time_t dateTimestamp = strToTimestamp(input_date);
    m_iterator it_element = btc_data.lower_bound(dateTimestamp);

    if (it_element == btc_data.end() || 
    (it_element->first != dateTimestamp && it_element != btc_data.begin()))
    {
        it_element--;
    }
    if (dateTimestamp < it_element->first)
        return (false);
    std::cout << input_date << "=> " << value << " = " << std::fixed << std::setprecision(2) << (value * it_element->second) << std::endl;
    std::cout.unsetf(std::ios::fixed);
    std::cout.precision(6);
    return (true);
}

void BitcoinExchange::exchange(const std::string &input_line) const
{
    double value;
    std::string date_part;
    std::string value_part;
    size_t separator_pos;

    separator_pos = input_line.find("|");
    if (separator_pos == std::string::npos)
    {
        std::cerr << "Error: bad input => " << input_line << std::endl;
        return ;
    }
    date_part = input_line.substr(0, separator_pos);
    value_part = input_line.substr(separator_pos + 1);
    if (!isValidInputDate(date_part)
    || !isValidInputValue(value_part))
    {
        std::cerr << "Error: bad input => " << input_line << std::endl;
        return ;
    }
    if (!valueConstraints(value_part, value))
        return ;
    if (!searchAndCalculate(date_part, value))
        std::cerr << "Error: date doesn't match the database" << std::endl;
}
