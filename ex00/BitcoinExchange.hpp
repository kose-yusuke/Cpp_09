/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:33:51 by koseki.yusu       #+#    #+#             */
/*   Updated: 2025/05/26 13:55:20 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include <map>
#include <cstdlib>

class BitcoinExchange{
    private:
        std::string _date;
        std::map<std::string, double> _database;
        bool isValidDate(std::string date);
        int _extractDatePart(const std::string& date, size_t start, size_t length);
    
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(BitcoinExchange const &other);
        BitcoinExchange &operator=(BitcoinExchange const &other);
        bool isInRange() const;
        std::string getDate() const;
        void loadDatabase(const std::string& filename);
        void processInput(const std::string& filename);
        bool isValidNumber(const std::string& str);
};
