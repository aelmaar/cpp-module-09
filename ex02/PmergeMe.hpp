/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:43:47 by ael-maar          #+#    #+#             */
/*   Updated: 2023/11/21 11:23:11 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>

# define INT_MAXLEN 10
# define SUCCESS 0
# define FAILURE 1

// ANSI ESCAPE CODES
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define RED_COLOR "\033[31m"
# define RESET "\033[0m"

typedef std::vector<int> int_vector;
typedef int_vector::iterator int_vector_it;
typedef std::vector<int_vector> int_vectors;
typedef int_vectors::iterator int_vectors_it;
typedef std::vector<std::pair<int_vector, int_vector> > v_pair;
typedef std::vector<std::pair<int_vector, int_vector> >::iterator v_pair_it;

typedef std::list<int> int_list;
typedef std::list<int>::iterator int_list_it;
typedef std::list<int_list> int_lists;
typedef int_lists::iterator int_lists_it;
typedef std::list<std::pair<int_list, int_list> > l_pair;
typedef std::list<std::pair<int_list, int_list> >::iterator l_pair_it;

/********************/
/* Prasing argument */
/********************/
bool parseArgs(char *argv[], int_vector &v);
bool ExceedIntMax(std::string &arg);
bool isOnlyDigits(std::string &arg);

/*******************/
/* Merge Insertion */
/*******************/

typedef struct MainIndexForVector
{
    int_vectors temp_mainchain;
    int_vector indexes;
} MainIndexForVector;

typedef struct MainIndexForList
{
    int_lists temp_mainchain;
    int_list indexes;
} MainIndexForList;

void MergeInsertionForList(int_list &originalNums, size_t numsSize, size_t pairsLen);
void MergeInsertionForVector(int_vector &originalNums, size_t numsSize, size_t pairsLen);

/*******************/
/*  SOME UTITLITY  */
/*******************/

template <typename Container>
void printFormatTime(clock_t &start, clock_t &end, Container &container, std::string const &containerName)
{
    double time_taken = (double(end - start) * 1000) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << container.size() << " elements with " << BOLD << UNDERLINE << containerName << RESET << ": ";
    std::cout << RED_COLOR << time_taken << RESET << " us" << std::endl;
}

template <typename Container>
void    printContainer(Container &container)
{
    typename Container::iterator it;

    for (it = container.begin(); it != container.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

#endif
