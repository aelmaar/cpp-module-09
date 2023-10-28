/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:37:48 by ael-maar          #+#    #+#             */
/*   Updated: 2023/10/28 15:07:58 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <ctime>
# include <map>
# include <sstream>
# include <fstream>
# include "utils.hpp"

typedef std::map<time_t, double>::const_iterator m_iterator;

class BitcoinExchange
{
    // private data members
    private:
        std::map<time_t, double> btc_data;
    // private member methods
    private:
        time_t strToTimestamp(const std::string &dateStr) const;
        bool isValidInputDate(const std::string &input_date) const;
        bool isValidInputValue(const std::string &input_value) const;
        bool parseDate(const std::string &input, int &year, int &month, int &day) const;
        bool AboveCurrentDate(int year, int month, int day) const;
        bool isDecimalNumber(const std::string& str) const;
        bool valueConstraints(const std::string &input_value, double &value) const;
        bool searchAndCalculate(const std::string &input_date, double value) const;
        m_iterator findClosestDate(time_t &timestampDate) const;
    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange const &src);
        BitcoinExchange &operator=(BitcoinExchange const &src);
        ~BitcoinExchange();
        void exchange(const std::string &input_line) const;
};

#endif
