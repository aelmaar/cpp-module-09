/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:43:47 by ael-maar          #+#    #+#             */
/*   Updated: 2023/11/18 16:51:04 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <list>
#include <algorithm>

# define INT_MAXLEN 10
# define SUCCESS 0
# define FAILURE 1

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

extern int comparisonCount;

/********************/
/* Prasing argument */
/********************/
bool parseArgs(char *argv[], int_vector &v);
bool ExceedIntMax(std::string &arg);
bool isOnlyDigits(std::string &arg);

/*******************/
/* Merge Insertion */
/*******************/

typedef struct MainIndex
{
    int_vectors temp_mainchain;
    int_vector indexes;
} MainIndex;

void MergeInsertion(int_vector &originalNums, size_t numsSize, size_t pairsLen);
int_vector JacobsthalSequence(int pendLen);
int jacobsthal(int n);
#endif
