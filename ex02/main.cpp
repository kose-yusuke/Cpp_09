/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:54:50 by koseki.yusu       #+#    #+#             */
/*   Updated: 2025/02/18 16:40:12 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool arg_validate(int argc, char **argv) 
{
    if (argc < 2) {
        std::cerr << "Error: not enough arg" << std::endl; 
        return false;
    }
    for (int i = 1; i < argc; i++) {
        for (int j = 0; argv[i][j] != '\0'; j++) {
            if (argv[i][j] < '0' || argv[i][j] > '9') {
                std::cerr << "Error: not number" << std::endl; 
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

static void output_after()
{
    std::cout << "After: ";
    
    std::cout << std::endl;
}

void mergeInsertionSort(std::vector<int>& vec)
{
    vec.push_back(1);
    vec.push_back(2);
}

std::vector<int> convertToVector(int argc, char **argv)
{
    std::vector<int> vec;
    for (int i = 1; i < argc; i++) {
        int num;
        std::istringstream iss(argv[i]);
        if (!(iss >> num)) {
            throw std::invalid_argument("Invalid number: " + std::string(argv[i]));
        }
        vec.push_back(std::strtol(argv[i], NULL, 10));
    }
    return vec;
}

std::deque<int> convertToDeque(int argc, char **argv)
{
    std::deque<int> deq;
    for (int i = 1; i < argc; i++) {
        int num;
        std::istringstream iss(argv[i]);
        if (!(iss >> num)) {
            throw std::invalid_argument("Invalid number: " + std::string(argv[i]));
        }
        deq.push_back(num);
    }
    return deq;
}

int main(int argc, char **argv)
{
    PmergeMe pmergeme;
    //validation
    if (!arg_validate(argc, argv))
        return 1;    
    
    //実行1_vector
    // 時間測定
    clock_t start1 = clock();
    // 引数をvectorにinit
    std::vector<int> vec = convertToVector(argc,argv);
    // ソート
    pmergeme.vec_sort(vec);
    // 時間止める
    clock_t end1 = clock();
    const double time1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1000.0;

    //実行2_deque
    // 時間測定
    clock_t start2 = clock();
    // 引数をdequeにinit
    std::deque<int> deq = convertToDeque(argc, argv);
    // ソート
    pmergeme.deq_sort(deq);
    // 時間止める
    clock_t end2 = clock();
    const double time2 = static_cast<double>(end2 - start2) / CLOCKS_PER_SEC * 1000.0;
    
    //出力
    output_before(argc, argv);
    output_after();
    std::cout << "Time to process a range of 5 elements with std::vector : " << time1 << " us" << std::endl;
    std::cout << "Time to process a range of 5 elements with std::deque : " << time2 << " us" << std::endl;
}