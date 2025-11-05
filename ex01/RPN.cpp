/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:27:16 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/05 12:29:52 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{}
RPN::RPN(std::string input)
{
	this->_parse_vector = this->parse_input(input);
}
RPN::RPN(const RPN& other)
{
	this->_stack = other._stack;
	this->_parse_vector = other._parse_vector;
}
RPN& RPN::operator=(const RPN& other)
{
	if(this == &other)
		return(*this);
	this->_stack = other._stack;
	this->_parse_vector = other._parse_vector;
	return(*this);
}
RPN::~RPN()
{
}
bool RPN::is_operator(std::string token)
{
	if (token.size() != 1)
	{
		return false;
	}
	char c = token[0];
	switch (c)
	{
		case '+':
		case '-':
		case '*':
		case '/':
			return(true);
	default:
			return false;
	}
}
bool RPN::is_nbr(std::string token)
{
	if (token.empty())
		return(false);
	else if (token.size() != 1)
		return(false);
	if (!std::isdigit(token[0]))
        return false;
	return(true);
}
bool RPN::check_token(std::string token)
{
	if (token.empty())
	{
		return false;
	}
	else if (!is_operator(token) && !is_nbr(token))
	{
		return(false);
	}
	return(true);
	
	
}
std::vector<std::string> RPN::parse_input(std::string input)
{
	if (input.empty())
	{
		throw ExceptionError("Error: the input is empty.");
	}
	std::istringstream iss(input);
	std::string temp;
	std::vector<std::string> tokens;
	while (iss >> temp)
	{
		tokens.push_back(temp);
	}
	for (std::vector<std::string>::iterator t = tokens.begin(); t != tokens.end(); ++t)
	{
    	if(!this->check_token(*t))
		{
			throw ExceptionError("Error: invalid input.");
		}
	}
	return tokens;
}
int RPN::operation(std::vector<std::string>::iterator t)
{
    int b = this->_stack.top();
    this->_stack.pop();
    int a = this->_stack.top();
    this->_stack.pop();

    int result = 0;

    if (*t == "+")
        result = a + b;
    else if (*t == "-")
        result = a - b;
    else if (*t == "*")
        result = a * b;
    else if (*t == "/")
    {
        if (b == 0)
            throw ExceptionError("Error: cannot divide by 0.");
        result = a / b;
    }

    this->_stack.push(result);
    return result;
}

int RPN::execute()
{
	std::vector<std::string>::iterator t = this->_parse_vector.begin();
	int result;
	for (; t != this->_parse_vector.end(); ++t)
	{
		if (is_nbr(*t))
		{
			this->_stack.push(std::atoi((*t).c_str()));
		}
		else if (is_operator(*t))
		{
			if (this->_stack.size() < 2)
			{
				throw ExceptionError("Error: invalid input.");
			}
			else
				result = operation(t);
		}
	}
	return(result);
}
