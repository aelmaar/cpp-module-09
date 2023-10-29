/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 18:10:56 by ael-maar          #+#    #+#             */
/*   Updated: 2023/10/29 15:37:51 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "./RPN [expression]" << std::endl;
        return (EXIT_FAILURE);
    }
    int result = execute(std::string(argv[1]));
    std::cout << result << std::endl;
    return (EXIT_SUCCESS);
}
