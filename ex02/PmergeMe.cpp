/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:05:28 by koseki.yusu       #+#    #+#             */
/*   Updated: 2025/05/14 15:18:41 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) 
{
    *this = other;
}
PmergeMe& PmergeMe::operator=(PmergeMe const &other)
{
    if (this != &other)
        *this = other;
    return *this;
}

static int binary_search_insert_pos(const std::vector<int>& sorted, int value)
{
    int left = 0;
    int right = sorted.size();
    while (left < right) {
        int mid = (left + right) / 2;
        if (value < sorted[mid])
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

void PmergeMe::vec_sort(std::vector<int>& vec) 
{
    if (vec.size() <= 1) 
        return;
    std::vector< std::pair<int,int> > pairs;
    for (int i = 0; i + 1 < (int)vec.size(); i += 2) {
        int a = vec[i], b = vec[i+1];
        if (a < b) 
            std::swap(a,b);
        pairs.push_back(std::make_pair(a,b));
    }
    bool is_odd = ((int)vec.size() % 2 == 1);
    int last = 0;
    if (is_odd) {
        last = vec[vec.size() - 1];
    }

    std::vector<int> main_chain;
    for (size_t j = 0; j < pairs.size(); ++j) {
        main_chain.push_back(pairs[j].first);
    }
    if (is_odd) 
        main_chain.push_back(last);
    
    vec_sort(main_chain);

    std::vector<int> insert_list;
    for (size_t j = 0; j < pairs.size(); ++j) {
        insert_list.push_back(pairs[j].second);
    }

    for (size_t k = 0; k < insert_list.size(); ++k) {
        int val = insert_list[k];
        int pos = binary_search_insert_pos(main_chain, val);
        main_chain.insert(main_chain.begin() + pos, val);
    }

    vec = main_chain;
}

static int binary_search_insert_pos_deq(const std::deque<int>& sorted, int value)
{
    int left  = 0;
    int right = sorted.size();
    while (left < right) {
        int mid = (left + right) / 2;
        if (value < sorted[mid])
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

void PmergeMe::deq_sort(std::deque<int>& deq)
{
    if (deq.size() <= 1)
        return;

    std::deque< std::pair<int,int> > pairs;
    for (size_t i = 0; i + 1 < deq.size(); i += 2) {
        int a = deq[i], b = deq[i+1];
        if (a < b) 
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }

    int last = 0;
    bool is_odd = (deq.size() % 2 == 1);
    if (is_odd) {
        last = deq[deq.size() - 1];
    }

    std::deque<int> main_chain;
    for (size_t j = 0; j < pairs.size(); ++j) {
        main_chain.push_back(pairs[j].first);
    }
    if (is_odd) {
        main_chain.push_back(last);
    }

    deq_sort(main_chain);

    std::deque<int> insert_list;
    for (size_t j = 0; j < pairs.size(); ++j) {
        insert_list.push_back(pairs[j].second);
    }

    for (size_t k = 0; k < insert_list.size(); ++k) {
        int val = insert_list[k];
        int pos = binary_search_insert_pos_deq(main_chain, val);
        main_chain.insert(main_chain.begin() + pos, val);
    }

    deq = main_chain;
}
