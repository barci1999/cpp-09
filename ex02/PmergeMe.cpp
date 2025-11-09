/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:12:19 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/09 18:14:21 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"PmergeMe.hpp"

/*****************************CANONICAL FORM***********************************/
PmergeMe::PmergeMe()
{}
PmergeMe::PmergeMe(char**argv)
{
	load_input(argv);
}
PmergeMe::PmergeMe(const PmergeMe& other)
{
	this->_deque = other._deque;
	this->_list = other._list;
}
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if(this == &other)
	{
		return *this;
	}
	this->_deque = other._deque;
	this->_list = other._list;
	return(*this);
}
PmergeMe::~PmergeMe(){	
}

std::ostream& operator<<(std::ostream& to_out,const PmergeMe& to_print)
{
	to_out << std::endl << "Deque: ";
	for (std::deque<int>::const_iterator it = to_print.getDeque().begin(); it != to_print.getDeque().end(); ++it)
		to_out << *it << " ";

	to_out << std::endl <<"List: ";
	for (std::list<int>::const_iterator it = to_print.getList().begin(); it != to_print.getList().end(); ++it)
		to_out << *it << " ";

	return to_out;
}

/*********************************PARSING*********************************/

bool PmergeMe::isValidNumber(const std::string &s) 
{
    if (s.empty()) 
		return false;
    for (size_t i = 0; i < s.size(); ++i)
	{
        if (!isdigit(s[i]))
				return false;
	}
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
			else
				{
					if(std::find(this->_deque.begin(),this->_deque.end(),std::atoi(token.c_str())) != this->_deque.end())
						throw ExceptionError("Error: duplicated element.");
					else
						this->_deque.push_back(std::atoi(token.c_str()));
					if (std::find(this->_list.begin(),this->_list.end(),std::atoi(token.c_str())) != this->_list.end())
						throw ExceptionError("Error: duplicated element.");
					else
						this->_list.push_back(std::atoi(token.c_str()));
				}
		}
	}
}
bool isSortedDeque(const std::deque<int>& dq)
{
	if (dq.empty()) 
	return true;
	for (std::deque<int>::const_iterator it = dq.begin(); it != dq.end() - 1; ++it) 
	{
		if (*it > *(it + 1))
		return false; 
	}
	return true;
}
bool isSortedList(const std::list<int>& lst)
{
	if (lst.empty()) 
	return true;
	std::list<int>::const_iterator it = lst.begin();
	std::list<int>::const_iterator next = it;
	++next;
	while (next != lst.end()) 
	{
		if (*it > *next)
		return false;
		++it;
		++next;
	}
	return true;
}

/******************************SORT METHODS**************************************/

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
	if (this->_deque.empty())
	{
		throw ExceptionError("Error: the deque container is empty");
	}
	
    std::cout << "---------Container deque-----------" << std::endl;

    std::cout << "Before: ";
    for (std::deque<int>::iterator i = this->_deque.begin(); i != this->_deque.end(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;

    fordJohnsonDeque(this->_deque);

    std::cout << "After: ";
    for (std::deque<int>::iterator i = this->_deque.begin(); i != this->_deque.end(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;
}
void PmergeMe::sortList()
{
	if (this->_list.empty())
	{
		throw("Error: the list container is empty");
	}
	
    std::cout << "---------Container list-----------" << std::endl;

    std::cout << "Before: ";
    for (std::list<int>::iterator it = this->_list.begin(); it != this->_list.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    fordJohnsonList(this->_list); 
    std::cout << "After: ";
    for (std::list<int>::iterator it = this->_list.begin(); it != this->_list.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}
