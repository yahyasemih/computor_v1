/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:40:28 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/20 08:23:07 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"

int main(int argc, char *argv[]) {
	int i = 1;
	int flags = 0;

	if (argc == 1) {
		std::cout << "usage: computor [-nv] \"equation\"" << std::endl;
		return 1;
	}

	while (i < argc - 1 && argv[i][0] == '-') {
		for (int j = 1; argv[i][j] != '\0'; ++j) {
			if (argv[i][j] == 'v') {
				flags |= F_VERBOSE;
			} else if (argv[i][j] == 'n') {
				flags |= F_NATURAL;
			} else {
				std::cout << "computor: illegal option -- " << argv[i][j]
					<< std::endl;
				std::cout << "usage: computor [-nv] \"equation\"" << std::endl;
				return 1;
			}
		}
		++i;
	}

	if (argc - i > 1) {
		std::cout << "usage: computor [-nv] \"equation\"" << std::endl;
		return 1;
	} else {
		computor c(argv[i], flags);
		c.compile();
		if (c.is_malformed_input())
			std::cout << "error: " << c.get_error_message() << std::endl;
		else {
			c.evaluate();
		}
	}
	return 0;
}
