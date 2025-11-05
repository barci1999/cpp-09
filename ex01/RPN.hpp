/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:58:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/05 14:13:37 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP
# include<algorithm>
# include<stack>
# include<iostream>
# include<string>
# include<sstream>
# include<vector>
class RPN
{
private:
	std::stack<int> _stack;
	std::vector<std::string> _parse_vector;
public:
	RPN();
	RPN(std::string input);
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

		class ExceptionError : public std::exception
                {
                        const char* _msg;
                        public:
                                explicit ExceptionError(const char* msg) : _msg(msg) {}
                                virtual const char* what() const throw(){
                                        return(_msg);
                                }
                };

	int execute();
	bool check_token(std::string token);
	std::vector<std::string> parse_input(std::string input);
	bool is_operator(std::string token);
	bool is_nbr(std::string token);
	int operation(std::vector<std::string>::iterator t);
};

#endif