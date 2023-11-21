/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:43:52 by ael-maar          #+#    #+#             */
/*   Updated: 2023/11/21 11:15:46 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    int_vector nums;
    int_list copy_nums;
    clock_t start, end;

    if (argc < 2)
    {
        std::cerr << "./PmergeMe [arguments]" << std::endl;
        return (FAILURE);
    }
    if (!parseArgs(argv, nums))
    {
        std::cerr << "ERROR" << std::endl;
        return (FAILURE);
    }
    copy_nums.assign(nums.begin(), nums.end());

    /* USING STD::VECTOR */

    std::cout << "before: ";
    printContainer(nums);
    start = clock();
    MergeInsertionForVector(nums, nums.size(), 1);
    end = clock();
    std::cout << "after: ";
    printContainer(nums);
    printFormatTime(start, end, nums, "std::vector");
    
    /* USING STD::LIST */
    start = clock();
    MergeInsertionForList(copy_nums, copy_nums.size(), 1);
    end = clock();
    printFormatTime(start, end, copy_nums, "std::list");
    return (SUCCESS);
}
