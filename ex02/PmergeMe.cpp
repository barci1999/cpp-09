/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:12:19 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/09 16:03:43 by pablalva         ###   ########.fr       */
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
{
	for (std::set<std::string>::iterator t = this->_input.begin(); t != this->_input.end(); t++)
	{
		int value = std::atoi(t->c_str());
		this->_deque.push_back(value);
	}
	
}
void PmergeMe::fordJohnsonDeque(std::deque<int>& deque)
{
	if (deque.size() <= 1)
	{
		return;
	}
	std::deque<int> smaller;
	std::deque<int> longer;
	for (size_t i = 0; i < deque.size(); i+= 2)
	{
		if (i + 1 < deque.size())
		{
			int first = deque[i];
			int second = deque[i + 1];
			if (first > second)
				std::swap(first,second);
			smaller.push_back(first);
			longer.push_back(second);
		}
		else
			smaller.push_back(deque[i]);
	}
	fordJohnsonDeque(smaller);
	for (size_t i = 0; i < longer.size(); ++i)
	{
		std::deque<int>::iterator t = std::lower_bound(smaller.begin(),smaller.end(),longer[i]);
		smaller.insert(t,longer[i]);
	}
	deque = smaller;
}
void PmergeMe::fordJohnsonList(std::list<int>& list)
{
	if (list.size() <= 1)
		return;
	std::list<int> smaller;
	std::list<int> longer;
	std::list<int>::iterator it = list.begin();
	while (it != list.end())
	{
		int first = *it;
		++it;

		if (it != list.end())
		{
			int second = *it;
			++it;

			if (first > second)
				std::swap(first, second);
			smaller.push_back(first);
			longer.push_back(second);
		}
		else
			smaller.push_back(first);
	}
	fordJohnsonList(smaller);
	std::list<int>::iterator i = longer.begin();
	while (i != longer.end())
	{
		std::list<int>::iterator temp = std::lower_bound(smaller.begin(),smaller.end(),*i);
		smaller.insert(temp,*i);
		i++;
	}
	list = smaller;
}
void PmergeMe::sortDeque()
{
    std::cout << "---------Container deque-----------" << std::endl;

    std::cout << "Before: ";
    for (std::deque<int>::iterator i = this->_deque.begin(); i != this->_deque.end(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;

    clock_t start = clock();
    fordJohnsonDeque(this->_deque);
    clock_t end = clock();

    double time = double(end - start) * 1000000 / CLOCKS_PER_SEC;

    std::cout << "After: ";
    for (std::deque<int>::iterator i = this->_deque.begin(); i != this->_deque.end(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << this->_deque.size()
              << " elements with std::deque : "
              << std::fixed << std::setprecision(5) << time << " us" << std::endl;
}
void PmergeMe::sortList()
{
    std::cout << "---------Container list-----------" << std::endl;

    std::cout << "Before: ";
    for (std::list<int>::iterator it = this->_list.begin(); it != this->_list.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    clock_t start = clock();
    fordJohnsonList(this->_list); 
    clock_t end = clock();

    double time_us = double(end - start) * 1000000 / CLOCKS_PER_SEC;

    std::cout << "After: ";
    for (std::list<int>::iterator it = this->_list.begin(); it != this->_list.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << this->_list.size()
              << " elements with std::list : "
              << std::fixed << std::setprecision(5) << time_us << " us" << std::endl;
}
void PmergeMe::insert_list()
{
	for (std::set<std::string>::iterator t = this->_input.begin(); t != this->_input.end(); t++)
	{
		int value = std::atoi(t->c_str());
		this->_list.push_back(value);
	}
}
std::ostream& operator<<(std::ostream& to_out,const PmergeMe& to_print)
{
	to_out << "Input strings: ";
		for (std::set<std::string>::const_iterator it = to_print.getInput().begin(); it != to_print.getInput().end(); ++it)
		to_out << *it << " ";
	to_out << std::endl << "Deque: ";
	for (std::deque<int>::const_iterator it = to_print.getDeque().begin(); it != to_print.getDeque().end(); ++it)
		to_out << *it << " ";

	to_out << std::endl <<"List: ";
	for (std::list<int>::const_iterator it = to_print.getList().begin(); it != to_print.getList().end(); ++it)
		to_out << *it << " ";

	return to_out;
}
