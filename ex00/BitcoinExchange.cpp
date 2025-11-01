/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:05:58 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/01 18:02:14 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
BitcoinExchange::BitcoinExchange()
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
BitcoinExchange::BitcoinExchange(char *file)
{
	loadDatabase (file);	
	for (std::map<std::string, double>::iterator it = this->_dataBase.begin(); it != _dataBase.end(); ++it)
	{
		std::cout << it->first << " => " << it->second << std::endl;
	}
	
}
BitcoinExchange::~BitcoinExchange(){}
void BitcoinExchange::loadDatabase(char *file)
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
		std::cout << value << std::endl;
		this->_dataBase[date] = value;
	}
}