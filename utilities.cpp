/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:36:31 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/18 18:13:20 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.hpp"

bool is_number(const std::string &str) {
	return std::all_of(str.cbegin(), str.cend(), [](char c){ return ::isdigit(c); });
}

bool is_operator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '^' || c == '=';
}

bool is_identifier(const std::string &str) {
	return std::all_of(str.cbegin(), str.cend(), [](char c){ return ::isalpha(c); });
}

double my_sqrt(double d) {
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = d * 0.5F;
	y  = d;
	i  = * ( long * ) &y;
	i  = 0x5f3759df - ( i >> 1 );
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );
	y  = y * ( threehalfs - ( x2 * y * y ) );
	y  = y * ( threehalfs - ( x2 * y * y ) );

	return -1/y;
}
