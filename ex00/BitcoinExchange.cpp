/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:05:58 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/03 15:19:46 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
BitcoinExchange::BitcoinExchange()
{
	loadDatabase("data.csv");
}
BitcoinExchange::BitcoinExchange(char *file)
{
	loadDatabase (file);
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	this->_dataBase = other._dataBase;
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this == &other)
	{
		return(*this);
	}
	this->_dataBase = other._dataBase;
	return(*this);
	
}
BitcoinExchange::~BitcoinExchange()
{
	
}
std::string BitcoinExchange::trim(std::string input)
{
	if (input.empty())
	{
		return("");
	}
	size_t start = 0;
	while (start < input.length() && std::isspace((unsigned char)input[start]))
    	start++;
	size_t end = input.length();
	while (end > start && std::isspace((unsigned char)input[end - 1]))
    	end--;
	return(input.substr(start,end - start));  
}
void BitcoinExchange::loadDatabase(const char *file)
{
	std::string file_name = trim((std::string)file);
	if (file_name.empty())
		throw ExceptionError("Error: the file name is empty.");
	std::ifstream fd_file(file_name.c_str());
	if (!fd_file.is_open())
		throw ExceptionError("Error: couldn't open file.");
	std::string temp;
	std::getline(fd_file,temp);
	while(std::getline(fd_file,temp))
	{
		if (temp.empty())
			continue;
		size_t pos = temp.find(',');
		if (pos == std::string::npos)
		{
			throw ExceptionError("Error: invalid format in the database file.");
		}
		std::string date = trim(temp.substr(0,pos));
		double value = std::strtod(trim(temp.substr(pos+1)).c_str(),NULL);
		this->_dataBase[date] = value;
	}
}
bool BitcoinExchange::is_validDate(std::string to_check)
{	
	if (to_check.length() != 10)
		return(false);
	else if (to_check[4] != '-' && to_check[7] != '-')
		return(false);
	std::string stryear = to_check.substr(0,4);
	std::string strmonth = to_check.substr(5,2);
	std::string strday = to_check.substr(8,2);
	for (size_t i = 0; i < stryear.size(); i++)
	{
        if (!std::isdigit(stryear[i])) 
			return false;
	}
    for (size_t i = 0; i < strmonth.size(); i++)
	{
        if (!std::isdigit(strmonth[i])) 
			return false;
	}
    for (size_t i = 0; i < strday.size(); i++)
	{
        if (!std::isdigit(strday[i])) 
			return false;
	}
		
	int year = std::atoi(stryear.c_str());
	int month = std::atoi(strmonth.c_str());
	int day = std::atoi(strday.c_str());
	if(year < 0)
		return(false);
	if (month < 1 || month > 12)
		return (false);
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap_year = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (leap_year)
        daysInMonth[1] = 29;
    if (day < 1 || day > daysInMonth[month - 1])
	{
        return false;
	}
	return(true);
}
bool BitcoinExchange::is_validValue(std::string to_check)
{
	if (to_check.empty())
	{
		std::cout << "Error: empty value." << std::endl;
		return false;
	}
    bool hasDecimal = false;
    for (size_t i = 0; i < to_check.size(); ++i)
    {
        char c = to_check[i];
        if (c == '.')
        {
            if (hasDecimal)
			{
				std::cout << "Error: invalid number -> " << to_check << std::endl;
                return false;
			}
            hasDecimal = true;
        }
        else if (!std::isdigit(c) && c != '-' && c != '+')
		{
			std::cout << "Error: invalid number -> "<< to_check << std::endl;
            return false;
		}
    }
	float value = std::atof(to_check.c_str());
	if (value < 0)
	{
		std::cout << "Error: not a positive number -> " << to_check << std::endl;
		return(false);
	}
	else if (value > 1000)
	{
		std::cout << "Error: too large a number -> " << to_check << std::endl;
		return(false);
	}
	return(true);
	
	
}
bool BitcoinExchange::check_format(std::string input)
{
	std::istringstream ss(input);
	std::string strDate,strValue;
	if (!std::getline(ss,strDate,'|') || !std::getline(ss,strValue))
	{
		std::cout << "Error: invalid format -> " << input << std::endl;
		return(false);
	}
	strDate = trim(strDate.c_str());
	strValue = trim(strValue.c_str());
	if (!is_validDate(strDate))
	{
		std::cout << "Error: invalid date -> " << strDate << std::endl;
		return(false);
	}
	if(!is_validValue(strValue))
	{
		return(false);
	}
	return(true);
}
void BitcoinExchange::print_values(std::string input)
{
    std::istringstream ss(input);
    std::string strDate, strValue;
    std::getline(ss, strDate, '|');
    std::getline(ss, strValue);
    strDate = trim(strDate.c_str());
    strValue = trim(strValue.c_str());

    std::map<std::string, double>::iterator it = this->_dataBase.find(strDate);

    if (it != this->_dataBase.end())
    {
        double value = std::strtod(strValue.c_str(), NULL);
        std::cout << strDate << " => " << strValue
                  << " = " << (value * it->second) << std::endl;
    }
    else
    {
        std::cout << "Error: date not found -> " << strDate << std::endl;
    }
}
void BitcoinExchange::multiply(std::ifstream& file)
{
	std::string input;
	bool first_line = true;
	while (std::getline(file,input))
	{
		if (first_line)
		{
			first_line = false;
			if(trim(input) != "date | value")
			{
				std::cout << trim(input) << std::endl;
				throw ExceptionError("Error: bad header in file.");
			}
		}
		else if(check_format(input))
		{
			print_values(input);
		}
	}
}