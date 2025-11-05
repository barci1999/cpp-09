/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:12:19 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/05 17:20:39 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"PmergeMe.hpp"
PmergeMe::PmergeMe()
{}
PmergeMe::PmergeMe(char**argv)
{
	load_input(argv);
	insert_deque();
	insert_list();
}
PmergeMe::PmergeMe(const PmergeMe& other)
{
	this->_deque = other._deque;
	this->_input = other._input;
	this->_list = other._list;
}
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if(this == &other)
	{
		return *this;
	}
	this->_deque = other._deque;
	this->_input = other._input;
	this->_list = other._list;
	return(*this);
}
PmergeMe::~PmergeMe(){
	
}
bool PmergeMe::isValidNumber(const std::string &s) 
{
    if (s.empty()) return false;
    for (size_t i = 0; i < s.size(); ++i)
        if (!isdigit(s[i])) return false;
    long n = std::atol(s.c_str());
    return n >= 0 && n <= INT_MAX;
}
void PmergeMe::load_input(char **argv)
{
	for (int i = 1; argv[i]; ++i)
	{
		std::istringstream iss(argv[i]);
		std::string token;

		while (iss >> token)
		{
			if (!isValidNumber(token))
				throw ExceptionError("Error: invalid input");
			if (!_input.insert(token).second)
				throw ExceptionError("Error: duplicate input");
		}
	}
}
void PmergeMe::insert_deque()
{}
void PmergeMe::insert_list()
{}
