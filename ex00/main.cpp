/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:06:00 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/01 19:47:14 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool check_valid_string(std::string input)
{
	std::string comprove = BitcoinExchange::trim(input);
	
}
int main(int argc,char **argv)
{
	if(argc != 2)
	{
		return(1);
	}
	try
	{
		BitcoinExchange b;
		std::string file(argv[1]);
		std::ifstream fd_file(file.c_str());
		if(!fd_file.is_open())
		{
			std::cout << "Error: could not open file." << std::endl;
			return(1);
		}
		b.multiply(fd_file);
		std::string input;
		std::string date;
		float value;
		while (std::getline(fd_file,input))
		{
			
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return(0);
}