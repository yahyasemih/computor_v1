/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:36:31 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/18 19:39:32 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.hpp"

bool is_number(const std::string &str) {
	return std::all_of(str.cbegin(), str.cend(),
		[](char c){ return ::isdigit(c); });
}

bool is_operator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '^' || c == '=';
}

bool is_identifier(const std::string &str) {
	return std::all_of(str.cbegin(), str.cend(),
		[](char c){ return ::isalpha(c); });
}

double my_sqrt(double d) {
	long l;
	float x, y;
	const float threehalfs = 1.5F;

	x = d * 0.5F;
	y  = d;
	l  = *(long *) &y;
	l  = 0x5f3759df - (l >> 1);
	y  = *(float *) &l;
	y  = y * (threehalfs - (x * y * y));
	y  = y * (threehalfs - (x * y * y));
	y  = y * (threehalfs - (x * y * y));

	return -1.0 / y;
}
