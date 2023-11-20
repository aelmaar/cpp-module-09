/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:43:52 by ael-maar          #+#    #+#             */
/*   Updated: 2023/11/20 13:07:17 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename Container>
void printFormatTime(clock_t &start, clock_t &end, Container &container, std::string const &containerName)
{
    double time_taken = (double(end - start) * 1000) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << container.size() << " elements with " << containerName << ": \033[31m" << time_taken << "\033[0m us" << std::endl;
}

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
    for (int_vector_it it = nums.begin(); it != nums.end(); it++)
        std::cout << *it << " ";
    std::cout << '\n';
    start = clock();
    MergeInsertionForVector(nums, nums.size(), 1);
    end = clock();
    std::cout << "after: ";
    for (int_vector_it it = nums.begin(); it != nums.end(); it++)
        std::cout << *it << " ";
    std::cout << '\n';
    printFormatTime(start, end, nums, "std::vector");
    
    /* USING STD::LIST */

    std::cout << "before: ";
    for (int_list_it it = copy_nums.begin(); it != copy_nums.end(); it++)
        std::cout << *it << " ";
    std::cout << '\n';
    start = clock();
    MergeInsertionForList(copy_nums, copy_nums.size(), 1);
    end = clock();
    std::cout << "after: ";
    for (int_list_it it = copy_nums.begin(); it != copy_nums.end(); it++)
        std::cout << *it << " ";
    std::cout << '\n';
    printFormatTime(start, end, copy_nums, "std::list");
    return (SUCCESS);
}
