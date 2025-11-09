/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:12:15 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/09 18:14:42 by pablalva         ###   ########.fr       */
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
		clock_t start = clock();
		pepe.sortDeque();
   		clock_t end = clock();
		double time_deque = double(end - start) * 1000 / CLOCKS_PER_SEC;
		start = clock();
		pepe.sortList();
		end = clock();
		double time_list = double(end - start) * 1000 / CLOCKS_PER_SEC;
    	std::cout << "Time to process a range of " << pepe.getDeque().size()
              	<< " elements with std::deque : " << std::fixed << std::setprecision(5) << time_deque << " us" << std::endl;
		std::cout << "Time to process a range of " << pepe.getList().size()
              	<< " elements with std::list : " << std::fixed << std::setprecision(5) << time_list << " us" << std::endl;
		if (!isSortedDeque(pepe.getDeque()))
    		std::cerr << "Error: deque no ordenado.\n";
		if (!isSortedList(pepe.getList()))
    		std::cerr << "Error: list no ordenada.\n";
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return(0);
}