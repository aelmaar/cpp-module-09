/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PMergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:43:49 by ael-maar          #+#    #+#             */
/*   Updated: 2023/11/08 10:52:52 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool isOnlyDigits(std::string &arg)
{
    size_t len = arg.length();

    for (size_t i = 0; i < len; i++)
    {
        if (!std::isdigit(arg[i]))
            return (false);
    }
    return (true);
}

bool ExceedIntMax(std::string &arg)
{
    size_t len = arg.length();
    size_t intConverted = 0;

    if (len > INT_MAXLEN)
        return (true);
    
    for (size_t i = 0; i < len; i++)
        intConverted = ((intConverted * 10) + static_cast<int>(arg[i]) - 48);
    if (intConverted > INT_MAX)
        return (true);
    return (false);
}

bool parseArgs(char *argv[], int_vector &v)
{
    int i = 1;
    while (argv[i])
    {
        std::string arg = argv[i];
        if (!isOnlyDigits(arg) || ExceedIntMax(arg))
            return (false);
        v.push_back(std::atoi(arg.c_str()));
        i++;
    }
    return (true);
}
