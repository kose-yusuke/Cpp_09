/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:33:51 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/12/12 14:12:55 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>
#include <exception>

class BitcoinExchange{
    private:
        int _day;
        int _month;
        int _year;
        std::string _date;
        void _stringToDate();
        bool _isValidDate(void) const;
    
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange(BitcoinExchange const &other);
        BitcoinExchange &operator=(BitcoinExchange const &other);
        bool isInRange(void) const;
        std::string getDate() const;
        
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
