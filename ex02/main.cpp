/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:54:50 by koseki.yusu       #+#    #+#             */
/*   Updated: 2025/05/14 15:47:36 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool arg_validate(int argc, char **argv) 
{
    if (argc < 2) {
        std::cerr << "Error: not enough arguments" << std::endl; 
        return false;
    }
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '\0') {
            std::cerr << "Error: empty argument" << std::endl;
            return false;
        }
        for (int j = 0; argv[i][j] != '\0'; j++) {
            if (argv[i][j] < '0' || argv[i][j] > '9') {
                std::cerr << "Error: invalid number '" << argv[i] << "'" << std::endl;
                return false;
            }
        }
    }
    return true;
}

static void output_before(int argc, char **argv)
{
    std::cout << "Before: ";
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;
}

// static void output_after(std::vector<int>& vec)
// {
//     std::cout << "After: ";
//     for (int i = 0; i < (int)vec.size(); i++) {
//         std::cout << vec[i] << " ";
//     }
//     std::cout << std::endl;
// }

static void output_after(std::deque<int>& deq)
{
    std::cout << "After: ";
    for (int i = 0; i < (int)deq.size(); i++) {
        std::cout << deq[i] << " ";
    }
    std::cout << std::endl;
}

std::vector<int> convertToVector(int argc, char **argv)
{
    std::vector<int> vec;
    for (int i = 1; i < argc; i++) {
        int num;
        std::istringstream iss(argv[i]);
        if (!(iss >> num) || num <= 0) {
            throw std::invalid_argument("Invalid positive number: " + std::string(argv[i]));
        }
        vec.push_back(num);
    }
    return vec;
}

std::deque<int> convertToDeque(int argc, char **argv)
{
    std::deque<int> deq;
    for (int i = 1; i < argc; i++) {
        int num;
        std::istringstream iss(argv[i]);
        if (!(iss >> num) || num <= 0) {
            throw std::invalid_argument("Invalid positive number: " + std::string(argv[i]));
        }
        deq.push_back(num);
    }
    return deq;
}

// static bool has_duplicates(const std::vector<int>& v) {
//     for (size_t i = 0; i + 1 < v.size(); ++i) {
//         for (size_t j = i + 1; j < v.size(); ++j) {
//             if (v[i] == v[j])
//                 return true;
//         }
//     }
//     return false;
// }

int main(int argc, char **argv)
{
    PmergeMe pmergeme;
    if (!arg_validate(argc, argv))
        return 1;    
    // std::vector<int> vec_input = convertToVector(argc,argv);
    // if (has_duplicates(vec_input)) {
    //         std::cerr << "Error: duplicate numbers detected" << std::endl;
    //         return 1;
    // }
    
    //実行1_vector
    clock_t start1 = clock();
    std::vector<int> vec = convertToVector(argc,argv);
    pmergeme.vec_sort(vec);
    clock_t end1 = clock();
    const double time1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1000.0;

    //実行2_deque
    clock_t start2 = clock();
    std::deque<int> deq = convertToDeque(argc, argv);
    pmergeme.deq_sort(deq);
    clock_t end2 = clock();
    const double time2 = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC * 1000.0;
    
    output_before(argc, argv);
    // output_after(vec);
    output_after(deq);
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << time1 << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : " << time2 << " us" << std::endl;
}