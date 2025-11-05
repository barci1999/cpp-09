/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:12:22 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/05 17:17:30 by pablalva         ###   ########.fr       */
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

class PmergeMe
{
private:
	std::deque<int> _deque;
	std::list<int> _list;
	std::set<std::string> _input;
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
	void insert_list();
	void insert_deque();
	void load_input(char **argv);
};

# endif