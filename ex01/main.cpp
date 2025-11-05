/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:23:49 by pablalva          #+#    #+#             */
/*   Updated: 2025/11/05 12:20:31 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"RPN.hpp"
int main(int argc ,char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: invalid number of arguments." << std::endl;
		return(1);
	}
	try
	{
		RPN program(argv[1]);
		int result;
		result = program.execute();
		std::cout << result <<std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	
}