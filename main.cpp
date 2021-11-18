/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:40:28 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/18 17:40:48 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cout << "Usage: computor \"equation\"" << std::endl;
		return 1;
	} else {
		computor c(argv[1]);
		c.compile();
		if (c.is_malformed_input())
			std::cout << "error: " << c.get_error_message() << std::endl;
		else {
			c.evaluate();
		}

	}
	return 0;
}
