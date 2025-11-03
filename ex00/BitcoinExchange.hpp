/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:05:55 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/03 16:48:40 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <iostream>
# include<string>
# include<map>
# include<fstream>
# include<sstream>
# include<cstdlib>
class BitcoinExchange
{
private:
	std::map<std::string,float> _dataBase;
public:
	BitcoinExchange(/* args */);
	BitcoinExchange(char* file);
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	class ExceptionError : public std::exception
                {
                        const char* _msg;
                        public:
                                explicit ExceptionError(const char* msg) : _msg(msg) {}
                                virtual const char* what() const throw(){
                                        return(_msg);
                                }
                };
	void loadDatabase(const char *file);
	void multiply(std::ifstream &file_fd);
	bool check_format(std::string input);
	bool is_validDate(std::string to_check);
	bool is_validValue(std::string to_check);
	static std::string trim(std::string input);
	void print_values(std::string input);
};

#endif