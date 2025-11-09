/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:12:22 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/09 18:03:35 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include<string>
# include<algorithm>
# include<iostream>
# include<sstream>
# include<deque>
# include<list>
# include<set>
# include<limits.h>
# include <ctime>
# include <iomanip> 
#include <sys/time.h> 
class PmergeMe
{
private:
	std::deque<int> _deque;
	std::list<int> _list;
public:
	PmergeMe();
	PmergeMe(char **argv);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	class ExceptionError : public std::exception
                {
                        const char* _msg;
                        public:
                                explicit ExceptionError(const char* msg) : _msg(msg) {}
                                virtual const char* what() const throw(){
                                        return(_msg);
                                }
                };

	
				
	bool isValidNumber(const std::string &s);
	void load_input(char **argv);
	
	
	void sortDeque();
	void fordJohnsonDeque(std::deque<int>& deque);
	
	void sortList();
	void fordJohnsonList(std::list<int>& lst);
	
	const std::deque<int>& getDeque() const { return _deque; }
	const std::list<int>& getList() const { return _list; }
};
bool isSortedList(const std::list<int>& lst);
bool isSortedDeque(const std::deque<int>& dq);
std::ostream& operator<<(std::ostream& to_out, const PmergeMe& to_print);

# endif