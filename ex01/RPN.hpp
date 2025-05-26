/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 23:18:54 by koseki.yusu       #+#    #+#             */
/*   Updated: 2025/05/26 16:00:35 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <stack>
#include <cmath>
#include <sstream>
#include <stdexcept>

class RPN{
    private:
        
    public:
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();
        double calculate(const std::string& expression);
        bool isOperator(const std::string &token);
        double applyOperation(const std::string &operation, double a, double b);
};