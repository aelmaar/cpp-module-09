/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:43:52 by ael-maar          #+#    #+#             */
/*   Updated: 2023/11/08 10:41:46 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    int_vector ints;

    if (argc < 2)
    {
        std::cerr << "./PmergeMe [arguments]" << std::endl;
        return (FAILURE);
    }
    if (!parseArgs(argv, ints))
    {
        std::cerr << "ERROR" << std::endl;
        return (FAILURE);
    }
    
    return (SUCCESS);
}
