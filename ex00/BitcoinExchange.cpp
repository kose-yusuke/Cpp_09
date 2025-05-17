/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koseki.yusuke <koseki.yusuke@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:33:30 by koseki.yusu       #+#    #+#             */
/*   Updated: 2025/05/17 14:19:26 by koseki.yusu      ###   ########.fr       */
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

// stringをintのdateに変換する(書式のエラーハンドリング含む)
void BitcoinExchange::_stringToDate(std::string date)
{
    std::istringstream ss;
    _date = date;

    if (date.size() != 10)
        throw ;
    for (int i=0;i<10;i++)
    {
        if ((i == 4 || i == 7) && date[i] != '-')
            throw dateException(*this);
        else if ((i != 4 && i != 7) && !isdigit(date[i]))
            throw dateException(*this);
    }
    
    _year = _extractDatePart(_date, 0, 4);
    _month = _extractDatePart(_date, 5, 2);
    _day = _extractDatePart(_date, 8, 2);

    if (!_isValidDate())
        throw dateException(*this);
}

// 日付関連のvalidate関数
bool BitcoinExchange::_isValidDate() const
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
            _stringToDate(date);
            if (_isValidDate())
                _database[date] = price;
            else
                throw std::runtime_error("Error: invalid date format in database.");
        }
    }
    file.close();
}

void BitcoinExchange::processInput(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open input file.");
        
    std::string header;
    std::getline(file, header);
    
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string date, valueStr;
        double value;

        if (std::getline(ss, date, '|') && std::getline(ss, valueStr))
        {
            date.erase(date.find_last_not_of(" \t\r\n") + 1);
            valueStr.erase(0, valueStr.find_first_not_of(" \t\r\n"));
            try
            {
                value = std::atof(valueStr.c_str());
                if (value > 1000)
                {
                    std::cerr << "Error: too large a number." << std::endl;
                    continue;
                }
                else if (value < 0)
                {
                    std::cerr << "Error: not a positive number." << std::endl;
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
            } catch (std::exception& e){
                std::cerr << "Error: invalid input => " << line << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: bad input => " << line << std::endl;
        }
    }
}

