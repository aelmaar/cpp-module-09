/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:37:51 by ael-maar          #+#    #+#             */
/*   Updated: 2023/10/28 17:36:15 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
    BitcoinExchange btc;
    (void)argc;
    (void)argv; 
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
