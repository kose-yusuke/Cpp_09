/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:33:51 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/12/13 14:00:04 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include <map>

class BitcoinExchange{
    private:
        int _day;
        int _month;
        int _year;
        std::string _date;
        std::map<std::string, double> _database;
        void _stringToDate(std::string date);
        bool _isValidDate() const;
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
        
        class dateException : public std::exception
        {
            public:
                dateException(const BitcoinExchange &obj)
                {
                    _msg = "invalid input"+ obj.getDate();
                }
                virtual const char *what() const throw(){
                    return _msg.c_str();
                }
                virtual ~dateException() throw() {}
            private:
                std::string _msg;
        };
};
