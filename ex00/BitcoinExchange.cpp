/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:33:30 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/12/12 12:16:26 by koseki.yusu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other)
{
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
    if (this != &other)
		*this = other;
	return (*this);    
}

bool BitcoinExchange::isValidDate(void) const
{
    int maxDay;
    if (_year < 0 || _month < 1 || _month > 12 || _day < 1)
        return false;
    switch (_month)
    {
        case 2:
            maxDay = 28;
            if (_year%4 == 0 && (_year%100 != 0 || _year%400 == 0))
                maxDay=29;
            break;
        case 4: case 6: case 9: case 11: maxDay=30; break;
        default: maxDay=31; break; 
    }
    return _day<=maxDay;
}


// 仮想通貨の取引が行われていたか
bool BitcoinExchange::isInRange(void) const
{
    
}