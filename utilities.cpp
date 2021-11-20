/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:36:31 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/20 18:12:34 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.hpp"
#include <iostream>

bool is_operator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '^' || c == '=';
}

static long double abs(long double d) {
	if (d < 0) {
		d = -d;
	}
	return d;
}

double my_sqrt(double d) {
	long double precision = 1e-10;
	long double low = 0;
	long double high = d;
	long double mid = (high + low) / 2.0;
	int iterations = 0;

	while (abs(mid * mid - (long double)d) > precision && iterations < 1000) {
		if (mid * mid > d) {
			high = mid;
		} else {
			low = mid;
		}
		mid = (high + low) / 2.0;

		++iterations;
	}

	return mid;
}
