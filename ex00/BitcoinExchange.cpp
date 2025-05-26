/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:33:30 by koseki.yusu       #+#    #+#             */
/*   Updated: 2025/05/26 13:54:13 by koseki.yusu      ###   ########.fr       */
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

int BitcoinExchange::_extractDatePart(const std::string& date, size_t start, size_t length)
{
    std::istringstream ss(date.substr(start, length));
    int result;
    ss >> result;
    return result;
}

bool BitcoinExchange::isValidDate(std::string date)
{
    std::istringstream ss;
    std::string tmp_date = date;
    
    if (tmp_date.size() != 10)
        return false;
    for (int i=0;i<10;i++)
    {
        if ((i == 4 || i == 7) && tmp_date[i] != '-')
            return false;
        else if ((i != 4 && i != 7) && !isdigit(tmp_date[i]))
            return false;
    }
    
    int year = _extractDatePart(tmp_date, 0, 4);
    int month = _extractDatePart(tmp_date, 5, 2);
    int day = _extractDatePart(tmp_date, 8, 2);

    int maxDay;
    if (year < 0 || month < 1 || month > 12 || day < 1)
        return false;
    switch (month)
    {
        case 2:
            maxDay = 28;
            if (year%4 == 0 && (year%100 != 0 || year%400 == 0))
                maxDay=29;
            break;
        case 4: case 6: case 9: case 11: maxDay=30; break;
        default: maxDay=31; break; 
    }
    return day<=maxDay;
}

// CSVファイルを読み込み、データベースに保存するメソッド
void BitcoinExchange::loadDatabase(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open database file.");
    
    std::string header;
    std::getline(file, header);

    std::string line;
    while (std::getline(file,line))
    {
        std::istringstream ss(line);
        std::string date;
        double price;
        if (std::getline(ss,date,',') && ss >> price)
        {
            if (isValidDate(date))
                _database[date] = price;
            else
                std::cerr << "Error: invalid date in database => " << date << std::endl;  
        }
    }
    file.close();
}

bool BitcoinExchange::isValidNumber(const std::string& str)
{
    if (str.empty())
        return false;

    size_t i = 0;

    if (str[i] == '+' || str[i] == '-')
        i++;

    bool hasDigit = false;
    bool hasDot = false;

    for (; i < str.length(); ++i)
    {
        if (str[i] >= '0' && str[i] <= '9') {
            hasDigit = true;
        }
        else if (str[i] == '.') {
            if (hasDot)
                return false;
            hasDot = true;
        }
        else {
            return false;
        }
    }

    return hasDigit;
}

void BitcoinExchange::processInput(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open input file.");
        
    std::string header;
    std::getline(file, header);

    std::string expectedHeader = "date | value";
    header.erase(header.find_last_not_of(" \t\r\n") + 1);
    header.erase(0, header.find_first_not_of(" \t\r\n"));

    if (header != expectedHeader)
        std::cerr << "Error: invalid header format. Expected 'date | value' => " << header << std::endl;
    
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string date, valueStr;
        double value;

        if (std::getline(ss, date, '|') && std::getline(ss, valueStr))
        {
            date.erase(date.find_last_not_of(" \t\r\n") + 1);
            date.erase(0, date.find_first_not_of(" \t\r\n"));
            if (date.empty())
            {
                std::cerr << "Error: bad input date => " << line << std::endl;
                continue;
            }
            else if (!isValidDate(date))
            {
                std::cerr << "Error: invalid date => " << line << std::endl;
                continue;   
            }
            valueStr.erase(0, valueStr.find_first_not_of(" \t\r\n"));
            
            if (!isValidNumber(valueStr))
            {
                std::cerr << "Error: not a number of input value => " << line << std::endl;
                continue;
            }
            
            value = std::atof(valueStr.c_str());
            
            if (value > 1000)
            {
                std::cerr << "Error: too large a number of input value => " << line << std::endl;
                continue;
            }
            else if (value < 0)
            {
                std::cerr << "Error: not a positive number of input value => " << line << std::endl;
                continue;
            }
            std::map<std::string, double>::iterator it = _database.lower_bound(date);
            if (it == _database.end() || it->first != date)
            {
                if (it != _database.begin())
                    --it;
            }
            if (it != _database.end())
            {
                double result = value * it->second;
                std::cout << date << " => " << value << " = " << result << std::endl;
            }
            else
            {
                std::cerr << "Error: no data available for date => " << date << std::endl;
            }            
        }
        else
        {
            std::cerr << "Error: bad input => " << line << std::endl;
        }
    }
}

