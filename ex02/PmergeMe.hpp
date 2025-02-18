/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:02:48 by koseki.yusu       #+#    #+#             */
/*   Updated: 2025/02/18 16:40:26 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <cstdlib>
#include <deque>
#include <vector>
#include <sstream>
#include <time.h>

class PmergeMe {
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(PmergeMe const &other);
        PmergeMe& operator=(PmergeMe const &other);

        void vec_sort(std::vector<int>& vec);
        void deq_sort(std::deque<int>& deq);
    private:
        template <typename T> void merge_insert_sort(T& container, int i);
};


// typenameのやつ描く
template <typename T> void PmergeMe::merge_insert_sort(T& container, int i)
{
    
}