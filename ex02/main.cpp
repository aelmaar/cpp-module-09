/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:43:52 by ael-maar          #+#    #+#             */
/*   Updated: 2023/11/18 18:39:24 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int comparisonCount = 0;

bool isSorted(const std::vector<int>& numbers)
{
    for (size_t i = 1; i < numbers.size(); i++)
    {
        if (numbers[i] < numbers[i - 1])
            return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    int_vector nums;

    // int_vector v = JacobsthalSequence(100000000); // to 7
    
    // std::cout << v << std::endl;
    // for (int i = 0; i < v.size(); i++)
    //     std::cout << v[i] << " ";
    // std::cout << '\n';
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
    std::cout << "before: ";
    for (int_vector::iterator it = nums.begin(); it != nums.end(); it++)
        std::cout << *it << " ";
    std::cout << '\n';
    MergeInsertion(nums, nums.size(), 1);
    std::cout << "after: ";
    for (int_vector::iterator it = nums.begin(); it != nums.end(); it++)
        std::cout << *it << " ";
    std::cout << '\n';
    std::cout << "Comparisons: " << comparisonCount << std::endl;
    std::cout << (isSorted(nums)? "TRUE":"FALSE") << std::endl;
    std::cout << "LENGTH: " << nums.size() << std::endl;
    return (SUCCESS);
}
