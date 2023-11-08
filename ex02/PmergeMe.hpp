/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:43:47 by ael-maar          #+#    #+#             */
/*   Updated: 2023/11/08 10:26:14 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>

# define INT_MAXLEN 10
# define SUCCESS 0
# define FAILURE 1

typedef std::vector<int> int_vector;

bool parseArgs(char *argv[], int_vector &v);
bool ExceedIntMax(std::string &arg);
bool isOnlyDigits(std::string &arg);

#endif
