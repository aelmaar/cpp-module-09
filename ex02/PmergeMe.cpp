/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:43:49 by ael-maar          #+#    #+#             */
/*   Updated: 2023/11/18 19:36:44 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void createPairs(int_vector &originalNums, v_pair &pairs, size_t numsSize, size_t &pairsLen)
{
    size_t i = 0;
    size_t pairsCreated = (numsSize / pairsLen) % 2 ? (numsSize / pairsLen - 1):(numsSize / pairsLen);

    while (pairsCreated > 0)
    {
        int_vector v1, v2;
        while (v1.size() != pairsLen)
            v1.push_back(originalNums[i++]);
        while (v2.size() != pairsLen)
            v2.push_back(originalNums[i++]);

        pairs.push_back(make_pair(v1, v2));
        pairsCreated -= 2;
    }
    // for (int i = 0; i < originalNums.size(); i++)
    //     std::cout << originalNums[i] << " ";
    // std::cout << '\n';
    // for (v_pair_it it = pairs.begin(); it != pairs.end(); it++)
    // {
    //     std::cout << "v1: ";
    //     for (int_vector_it it_v = it->first.begin(); it_v != it->first.end(); it_v++)
    //         std::cout << *it_v << " ";
    //     std::cout << "| ";
    //     std::cout << "v2: ";
    //     for (int_vector_it it_v = it->second.begin(); it_v != it->second.end(); it_v++)
    //         std::cout << *it_v << " ";
    //     std::cout << "| ";
    // }
    // std::cout << '\n';
}

void MergeAndUpdate(int_vector &originalNums, v_pair &pairs)
{
    v_pair_it it;
    int_vector_it v_it;
    size_t i = 0;
    
    for (it = pairs.begin(); it != pairs.end(); it++)
    {
        if (it->first.back() > it->second.back())
        {
            for (v_it = it->second.begin(); v_it != it->second.end(); v_it++)
                originalNums[i++] = *v_it;
            for (v_it = it->first.begin(); v_it != it->first.end(); v_it++)
                originalNums[i++] = *v_it;
        } else
            i += (it->first.size() * 2);
        comparisonCount++;
    }
}

int jacobsthal(int n)
{
    if (n == 0)
        return (0);
    if (n == 1)
        return (1);
    return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

int_vector JacobsthalSequence(int pendLen)
{
    int_vector sequence;

    for (int start = 3; jacobsthal(start) < pendLen; start++)
    {
        sequence.push_back(jacobsthal(start - 1));
    }
    return (sequence);
}

bool compare(const int_vector &a, const int_vector &b)
{
    comparisonCount++;
    return (a.back() < b.back());
}

int_vector generateSortedNumbers(size_t n)
{
    int_vector nums;

    for (size_t i = 0; i < n; i++)
    {
        nums.push_back(i);
    }
    return (nums);
}

void updateMainIndexes(int_vectors &mainchain, MainIndex &mainIndexes)
{
    size_t i, j;

    i = j = 0;
    for (int_vectors_it it = mainchain.begin(); it != mainchain.end(); it++, i++)
    {
        if (it->back() == mainIndexes.temp_mainchain[j].back())
            mainIndexes.indexes[j++] = i;
        if (j >= mainIndexes.temp_mainchain.size())
            break;
    }
}

void insertAndUpdateMainchain(int_vectors &mainchain, MainIndex &mainIndexes, int_vectors &pend, size_t pendIndex) {
    int_vectors_it it;

    if (pendIndex < mainIndexes.indexes.size())
        it = std::lower_bound(mainchain.begin(), mainchain.begin() + mainIndexes.indexes.at(pendIndex), pend.at(pendIndex), compare);
    else
        it = std::lower_bound(mainchain.begin(), mainchain.end(), pend.at(pendIndex), compare);
    mainchain.insert(it, pend.at(pendIndex));
    updateMainIndexes(mainchain, mainIndexes);
}

void insertAndUpdate(int_vector &originalNums, int_vectors &mainchain, int_vectors &pend)
{
    size_t pendIndex = 0, jacobIndex = 1, pendSize = pend.size(), i;
    static int_vector jacob = JacobsthalSequence(1000000000);
    MainIndex mainIndexes = {mainchain, generateSortedNumbers(mainchain.size())};

    if (pend.size() > 0)
    {
        mainchain.insert(mainchain.begin(), *pend.begin());
        updateMainIndexes(mainchain, mainIndexes);
        pendIndex = (size_t)jacob[jacobIndex] > pendSize ? pendSize:jacob[jacobIndex];
        while (pendIndex <= pendSize)
        {
            for (size_t i = pendIndex - 1; i >= (size_t)jacob[jacobIndex - 1]; i--)
                insertAndUpdateMainchain(mainchain, mainIndexes, pend, i);
            if (pendIndex == pendSize)
                break;
            pendIndex = (size_t)jacob[++jacobIndex] > pendSize ? pendSize:jacob[jacobIndex];
        }
        // update the original container
        i = 0;
        for (int_vectors_it d_it = mainchain.begin(); d_it != mainchain.end(); d_it++)
        {
            for (int_vector_it s_it = d_it->begin(); s_it != d_it->end(); s_it++)
                originalNums[i++] = *s_it;
        }
    }
}

void Insertion(int_vector &originalNums, size_t numsSize, size_t pairsLen)
{
    int_vectors mainchain, pend;
    size_t newSize = (numsSize / pairsLen) % 2 ? numsSize - pairsLen:numsSize;
    size_t i = 0;

    while (i < newSize)
    {
        int_vector temp;
        while (temp.size() != pairsLen)
            temp.push_back(originalNums[i++]);
        pend.push_back(temp);
        temp.clear();
        while (temp.size() != pairsLen)
            temp.push_back(originalNums[i++]);
        mainchain.push_back(temp);
    }
    int_vector temp;
    while (i < numsSize)
        temp.push_back(originalNums[i++]);
    if (!temp.empty())
        pend.push_back(temp);
    insertAndUpdate(originalNums, mainchain, pend);
}

void MergeInsertion(int_vector &originalNums, size_t numsSize, size_t pairsLen)
{
    v_pair pairs;
    size_t newSize = (numsSize / pairsLen) % 2 ? numsSize - pairsLen:numsSize;

    if (pairsLen == numsSize)
        return;
    createPairs(originalNums, pairs, numsSize, pairsLen);
    MergeAndUpdate(originalNums, pairs);
    MergeInsertion(originalNums, newSize, pairsLen * 2);
    Insertion(originalNums, numsSize, pairsLen);
}
