/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:05:28 by koseki.yusu       #+#    #+#             */
/*   Updated: 2025/05/18 20:54:17 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// int g_vec_count = 0;
int g_deq_count = 0;

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

static size_t jacobsthal(size_t n) {
    if (n == 0) 
        return 0;
    if (n == 1) 
        return 1;
    return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

static std::vector<size_t> get_jacobsthal_order_vector(size_t n) {
    
    std::vector<size_t> order;

    order.push_back(0);

    size_t i = 2;
    
    while (n >= (jacobsthal(i) - jacobsthal(i - 1)))
    {
        size_t tmp_jacob = jacobsthal(i);
        while (tmp_jacob > jacobsthal(i - 1))
        {
            if (tmp_jacob - 1 < n)
                order.push_back(tmp_jacob - 1);
            tmp_jacob--;
        }
        i++;
    }

    return order;
}

static int binary_search_insert_pos(const std::vector<int>& sorted, int value, size_t right_limit)
{
    int left = 0;
    int right = static_cast<int>(right_limit);
    while (left < right) {
        int mid = (left + right) / 2;
        if (value < sorted[mid])
            right = mid;
        else
            left = mid + 1;
        // g_vec_count++;
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
        {
            std::swap(a,b);
            // g_vec_count++;   
        }
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

    // std::cout << "[DEBUG] main_chain after recursion: ";
    // for (size_t i = 0; i < main_chain.size(); ++i) {
    //     std::cout << main_chain[i];
    // }
    // std::cout << std::endl;

    std::vector<int> insert_list;
    for (size_t j = 0; j < pairs.size(); ++j) {
        insert_list.push_back(pairs[j].second);
    }

    std::vector<size_t> jacob_order = get_jacobsthal_order_vector(insert_list.size());

    // std::cout << "[DEBUG] Jacob insertion order: ";
    // for (size_t i = 0; i < jacob_order.size(); ++i) {
    //     std::cout << jacob_order[i] << " ";
    // }
    // std::cout << std::endl;

    std::vector<size_t> first_pair_indices;
    for (size_t i = 0; i < main_chain.size(); ++i) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (main_chain[i] == pairs[j].first) {
                first_pair_indices.push_back(j);
                break;
            }
        }
    }

    for (size_t i = 0; i < jacob_order.size(); ++i) {
        size_t idx_in_main_chain = jacob_order[i];
        size_t pair_index = first_pair_indices[idx_in_main_chain];
        
        int first = pairs[pair_index].first;
        int second = pairs[pair_index].second;
    
        size_t first_pos = 0;
        for (size_t k = 0; k < main_chain.size(); ++k) {
            if (main_chain[k] == first) {
                first_pos = k;
                break;
            }
        }

        int insert_pos = binary_search_insert_pos(main_chain, second, first_pos);
        
        // std::cout << "[DEBUG] [step " << i << "] inserting second=" << second
        //       << " (pair_index=" << pair_index << ") from pair(" << first << "," << second << ")"
        //       << " at pos=" << insert_pos << ", first_pos=" << first_pos
        //       << std::endl;
    
        main_chain.insert(main_chain.begin() + insert_pos, second);
    }

    vec = main_chain;
    // std::cout << "vec_count : " << g_vec_count << std::endl;
}

static int binary_search_insert_pos_deq(const std::deque<int>& sorted, int value, size_t right_limit)
{
    int left  = 0;
    int right = static_cast<int>(right_limit);
    while (left < right) {
        int mid = (left + right) / 2;
        if (value < sorted[mid])
            right = mid;
        else
            left = mid + 1;
        // g_deq_count++;
    }
    return left;
}

static std::deque<size_t> get_jacobsthal_order_deque(size_t n) {
    std::deque<size_t> order;

    order.push_back(0);

    size_t i = 2;
    
    while (n >= (jacobsthal(i) - jacobsthal(i - 1)))
    {
        size_t tmp_jacob = jacobsthal(i);
        while (tmp_jacob > jacobsthal(i - 1))
        {
            if (tmp_jacob - 1 < n)
                order.push_back(tmp_jacob - 1);
            tmp_jacob--;
        }
        i++;
    }

    return order;
}


void PmergeMe::deq_sort(std::deque<int>& deq)
{
    if (deq.size() <= 1)
        return;

    std::deque< std::pair<int,int> > pairs;
    for (size_t i = 0; i + 1 < deq.size(); i += 2) {
        int a = deq[i], b = deq[i+1];
        if (a < b) 
        {
            std::swap(a, b);
            // g_deq_count++;   
        }
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

    std::deque<size_t> jacob_order = get_jacobsthal_order_deque(insert_list.size());

    std::deque<size_t> first_pair_indices;
    for (size_t i = 0; i < main_chain.size(); ++i) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (main_chain[i] == pairs[j].first) {
                first_pair_indices.push_back(j);
                break;
            }
        }
    }

    for (size_t i = 0; i < jacob_order.size(); ++i) {
        size_t idx_in_main_chain = jacob_order[i];
        size_t pair_index = first_pair_indices[idx_in_main_chain];
        
        int first = pairs[pair_index].first;
        int second = pairs[pair_index].second;
    
        size_t first_pos = 0;
        for (size_t k = 0; k < main_chain.size(); ++k) {
            if (main_chain[k] == first) {
                first_pos = k;
                break;
            }
        }

        int insert_pos = binary_search_insert_pos_deq(main_chain, second, first_pos);    
        main_chain.insert(main_chain.begin() + insert_pos, second);
    }

    deq = main_chain;
    // std::cout << "deq_count : " << g_deq_count << std::endl;
}
