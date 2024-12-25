/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:05:28 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/12/25 13:27:35 by koseki.yusu      ###   ########.fr       */
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

void PmergeMe::vec_sort(std::vector<int>& vec) 
{
    
}

void PmergeMe::deq_sort(std::deque<int>& deque)
{
    
}
