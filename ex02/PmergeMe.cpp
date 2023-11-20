/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:43:49 by ael-maar          #+#    #+#             */
/*   Updated: 2023/11/20 13:01:56 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*********************************/

/*       USING STD::VECTOR       */   

/*********************************/

void createPairsForVector(int_vector &originalNums, v_pair &pairs, size_t numsSize, size_t &pairsLen)
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
}

void MergeAndUpdateForVector(int_vector &originalNums, v_pair &pairs)
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

void updateMainIndexesForVector(int_vectors &mainchain, MainIndexForVector &mainIndexes)
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

void insertAndUpdateMainchainForVector(int_vectors &mainchain, MainIndexForVector &mainIndexes, int_vectors &pend, size_t pendIndex) {
    int_vectors_it it;

    if (pendIndex < mainIndexes.indexes.size())
        it = std::lower_bound(mainchain.begin(), mainchain.begin() + mainIndexes.indexes.at(pendIndex), pend.at(pendIndex), compare);
    else
        it = std::lower_bound(mainchain.begin(), mainchain.end(), pend.at(pendIndex), compare);
    mainchain.insert(it, pend.at(pendIndex));
    updateMainIndexesForVector(mainchain, mainIndexes);
}

void insertAndUpdateForVector(int_vector &originalNums, int_vectors &mainchain, int_vectors &pend)
{
    size_t pendIndex = 0, jacobIndex = 1, pendSize = pend.size(), i;
    static int_vector jacob = JacobsthalSequence(1000000000);
    MainIndexForVector mainIndexes = {mainchain, generateSortedNumbers(mainchain.size())};

    if (pend.size() > 0)
    {
        mainchain.insert(mainchain.begin(), *pend.begin());
        updateMainIndexesForVector(mainchain, mainIndexes);
        pendIndex = (size_t)jacob[jacobIndex] > pendSize ? pendSize:jacob[jacobIndex];
        while (pendIndex <= pendSize)
        {
            for (size_t i = pendIndex - 1; i >= (size_t)jacob[jacobIndex - 1]; i--)
                insertAndUpdateMainchainForVector(mainchain, mainIndexes, pend, i);
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

void InsertionForVector(int_vector &originalNums, size_t numsSize, size_t pairsLen)
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
    insertAndUpdateForVector(originalNums, mainchain, pend);
}

void MergeInsertionForVector(int_vector &originalNums, size_t numsSize, size_t pairsLen)
{
    v_pair pairs;
    size_t newSize = (numsSize / pairsLen) % 2 ? numsSize - pairsLen:numsSize;

    if (pairsLen == numsSize)
        return;
    createPairsForVector(originalNums, pairs, numsSize, pairsLen);
    MergeAndUpdateForVector(originalNums, pairs);
    MergeInsertionForVector(originalNums, newSize, pairsLen * 2);
    InsertionForVector(originalNums, numsSize, pairsLen);
}

/*********************************/

/*       USING STD::LIST         */   

/*********************************/

void createPairsForList(int_list &originalNums, l_pair &pairs, size_t numsSize, size_t &pairsLen)
{
    size_t pairsCreated = (numsSize / pairsLen) % 2 ? (numsSize / pairsLen - 1):(numsSize / pairsLen);
    int_list_it original_it = originalNums.begin();

    while (pairsCreated > 0)
    {
        int_list v1, v2;
        while (v1.size() != pairsLen)
        {
            v1.push_back(*original_it);
            original_it++;
        }
        while (v2.size() != pairsLen)
        {
            v2.push_back(*original_it);
            original_it++;
        }
        pairs.push_back(make_pair(v1, v2));
        pairsCreated -= 2;
    }
}

void MergeAndUpdateForList(int_list &originalNums, l_pair &pairs)
{
    l_pair_it it;
    int_list_it v_it;
    int_list_it l_it = originalNums.begin();

    for (it = pairs.begin(); it != pairs.end(); it++)
    {
        if (it->first.back() > it->second.back())
        {
            for (v_it = it->second.begin(); v_it != it->second.end(); v_it++, l_it++)
                *l_it = *v_it;
            for (v_it = it->first.begin(); v_it != it->first.end(); v_it++, l_it++)
                *l_it = *v_it;
        } else
            std::advance(l_it, it->first.size() * 2);
    }
}

bool compareForList(const int_list &a, const int_list &b)
{
    return (a.back() < b.back());
}

int_list generateSortedNumbersForList(size_t n)
{
    int_list nums;

    for (size_t i = 0; i < n; i++)
    {
        nums.push_back(i);
    }
    return (nums);
}

void updateMainIndexesForList(int_lists &mainchain, MainIndexForList &mainIndexes)
{
    size_t i = 0;
    int_lists_it temp_it = mainIndexes.temp_mainchain.begin();
    int_list_it index_it = mainIndexes.indexes.begin();

    for (int_lists_it it = mainchain.begin(); it != mainchain.end(); it++, i++)
    {
        if (it->back() == temp_it->back())
        {
            *index_it = i;
            index_it++;
            temp_it++;
        }
        if (temp_it == mainIndexes.temp_mainchain.end())
            break;
    }
}

void insertAndUpdateMainchainForList(int_lists &mainchain, MainIndexForList &mainIndexes, int_lists &pend, size_t pendIndex) {
    int_lists_it it, pend_it = pend.begin(), mainchain_it = mainchain.begin();
    int_list_it index_it = mainIndexes.indexes.begin();

    std::advance(index_it, pendIndex);
    std::advance(pend_it, pendIndex);
    std::advance(mainchain_it, *index_it);
    if (pendIndex < mainIndexes.indexes.size())
        it = std::lower_bound(mainchain.begin(), mainchain_it, *pend_it, compareForList);
    else
        it = std::lower_bound(mainchain.begin(), mainchain.end(), *pend_it, compareForList);
    mainchain.insert(it, *pend_it);
    updateMainIndexesForList(mainchain, mainIndexes);
}

void insertAndUpdateForList(int_list &originalNums, int_lists &mainchain, int_lists &pend)
{
    size_t pendIndex = 0, jacobIndex = 1, pendSize = pend.size();
    static int_vector jacob = JacobsthalSequence(1000000000);
    MainIndexForList mainIndexes = {mainchain, generateSortedNumbersForList(mainchain.size())};

    if (pend.size() > 0)
    {
        mainchain.insert(mainchain.begin(), *pend.begin());
        updateMainIndexesForList(mainchain, mainIndexes);
        pendIndex = (size_t)jacob[jacobIndex] > pendSize ? pendSize:jacob[jacobIndex];
        while (pendIndex <= pendSize)
        {
            for (size_t i = pendIndex - 1; i >= (size_t)jacob[jacobIndex - 1]; i--)
                insertAndUpdateMainchainForList(mainchain, mainIndexes, pend, i);
            if (pendIndex == pendSize)
                break;
            pendIndex = (size_t)jacob[++jacobIndex] > pendSize ? pendSize:jacob[jacobIndex];
        }
        // update the original container
        int_list_it original_it = originalNums.begin();
        for (int_lists_it d_it = mainchain.begin(); d_it != mainchain.end(); d_it++)
        {
            for (int_list_it s_it = d_it->begin(); s_it != d_it->end(); s_it++)
            {
                *original_it = *s_it;
                original_it++;
            }
        }
    }
}

void InsertionForList(int_list &originalNums, size_t numsSize, size_t pairsLen)
{
    int_lists mainchain, pend;
    int_list_it original_it = originalNums.begin();
    size_t newSize = (numsSize / pairsLen) % 2 ? numsSize - pairsLen:numsSize;
    size_t i = 0;

    while (i < newSize)
    {
        int_list temp;
        while (temp.size() != pairsLen)
            temp.push_back(*(original_it++));
        pend.push_back(temp);
        temp.clear();
        while (temp.size() != pairsLen)
            temp.push_back(*(original_it++));
        mainchain.push_back(temp);
        i += (pairsLen * 2);
    }
    int_list temp;
    while (i < numsSize)
    {
        temp.push_back(*(original_it++));
        i++;
    }
    if (!temp.empty())
        pend.push_back(temp);
    insertAndUpdateForList(originalNums, mainchain, pend);
}

void MergeInsertionForList(int_list &originalNums, size_t numsSize, size_t pairsLen)
{
    l_pair pairs;
    size_t newSize = (numsSize / pairsLen) % 2 ? numsSize - pairsLen:numsSize;

    if (pairsLen == numsSize)
        return;
    createPairsForList(originalNums, pairs, numsSize, pairsLen);
    MergeAndUpdateForList(originalNums, pairs);
    MergeInsertionForList(originalNums, newSize, pairsLen * 2);
    InsertionForList(originalNums, numsSize, pairsLen);
}