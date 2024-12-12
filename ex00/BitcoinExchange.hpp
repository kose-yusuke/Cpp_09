/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:33:51 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/12/12 11:47:31 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <iostream>

class Date{
    private:
        int _day;
        int _month;
        int _year;
    
    public:
        Date();
        ~Date();
        Date(Date const &other);
        Date &operator=(Date const &other);
        bool isValidDate(void) const;
};

class DateAndPrice{
    private: 
        std::string database;
    public:
        DateAndPrice();
        ~DateAndPrice();
        DateAndPrice(DateAndPrice const &other);
        DateAndPrice &operator=(DateAndPrice const &other);
};