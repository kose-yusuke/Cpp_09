/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:33:30 by koseki.yusu       #+#    #+#             */
/*   Updated: 2024/12/12 14:15:06 by koseki.yusu      ###   ########.fr       */
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

std::string BitcoinExchange::getDate() const
{
    return _date;
}

void BitcoinExchange::_stringToDate()
{
    std::string date;
    date = _date;

    if (date.size() != 10)
        throw ;
    for (int i=0;i<10;i++)
    {
        if ((i == 4 || i == 7) && date[i] != '-')
            throw dateException(*this);
        else if ((i != 4 && i != 7) && !isdigit(date[i]))
            throw dateException(*this);
    }
    
    // 2009-01-02
    _year = std::stoi(date.substr(0,4));
    _month = std::stoi(date.substr(5,2));
    _day = std::stoi(date.substr(8,2));

    if (!_isValidDate())
        throw dateException(*this);
}

bool BitcoinExchange::_isValidDate(void) const
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
// bool BitcoinExchange::isInRange(void) const
// {
    
// }