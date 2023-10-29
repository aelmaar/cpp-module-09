/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:37:51 by ael-maar          #+#    #+#             */
/*   Updated: 2023/10/29 16:58:07 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
    try
    {
        BitcoinExchange btc;
        if (argc != 2)
        {
            std::cerr << "Error: Invalid argument" << std::endl;
            return (EXIT_FAILURE);
        }
        std::ifstream input_read(argv[1]);
        std::string line;
        if (!input_read.is_open())
        {
            std::cerr << "Error: " << strerror(errno) << std::endl;
            return (EXIT_FAILURE);
        }
        std::getline(input_read, line);
        if (line != "date | value")
        {
            std::cerr << "Error: the input file is invalid" << std::endl;
            return (EXIT_FAILURE);
        }
        while (std::getline(input_read, line))
        {
            if (line.empty())
                continue;
            btc.exchange(line);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
