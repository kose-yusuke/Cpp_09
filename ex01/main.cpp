/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 23:18:32 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/12/15 15:23:56 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) 
    {
        std::cerr << "Error: Usage: ./RPN \"expression\"" << std::endl;
        return 1;
    }

    try {
        RPN rpn;
        double result;
        result = rpn.calculate(argv[1]);
        std::cout << result << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
}