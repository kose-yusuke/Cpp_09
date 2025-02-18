/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 23:18:51 by koseki.yusu       #+#    #+#             */
/*   Updated: 2025/02/18 16:36:29 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN ( RPN const &other ) {
    (void)other;
}

RPN &RPN::operator=( RPN const &other) {
    (void)other;
    return *this;
}

RPN::~RPN () {}

double stringToDouble(const std::string &str)
{
    std::stringstream ss(str);
    double value;
    ss >> value;
    if (ss.fail()) {
        throw std::runtime_error("Invalid number: " + str);
    }
    return value;
}

bool RPN::isOperator(const std::string &token) 
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

double RPN::applyOperation(const std::string &operation, double a, double b)
{
    if (operation == "+") return a + b;
    if (operation == "-") return a - b;
    if (operation == "*") return a * b;
    if (operation == "/") {
        if (b == 0) {
            throw std::runtime_error("Division by zero.");
        }
        return a / b;
    }
    throw std::runtime_error("Unknown operator: " + operation);
}

double RPN::calculate(const std::string &expression)
{
    std::istringstream iss(expression);
    std::string token;
    std::stack<double> stack;

    while (iss >> token)
    {
        if (isdigit(token[0]))
            stack.push(stringToDouble(token));
        else if (isOperator(token))
        {
            if (stack.size() < 2) 
                throw std::runtime_error("Not enough number");
            double b = stack.top(); 
            stack.pop();
            double a = stack.top(); 
            stack.pop();
            stack.push(applyOperation(token,a,b));
        }
        else
            throw std::runtime_error("Invalid token: " + token);
            
    }
    
    if (stack.size() != 1)
        throw std::runtime_error("Invalid RPN");
    return stack.top();
}