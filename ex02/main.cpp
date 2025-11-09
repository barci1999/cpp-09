/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:12:15 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/09 15:36:31 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
int main(int argc,char **argv)
{
	if (argc < 2)
	{
		std::cout << "invalid number of arguments."<<std::endl;
		return(1);
	}
	try
	{
		PmergeMe pepe(argv);
		pepe.sortDeque();
		pepe.sortList();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}