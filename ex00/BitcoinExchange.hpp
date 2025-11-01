/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:05:55 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/01 17:51:02 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <iostream>
# include<string>
# include<map>
# include<fstream>
# include<cstdlib>
class BitcoinExchange
{
private:
	std::map<std::string,double> _dataBase;
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
	void loadDatabase(char *file);
	std::string trim(std::string input);
};

#endif