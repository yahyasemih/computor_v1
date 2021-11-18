/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:36:31 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/18 17:59:38 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.hpp"
#include <cmath>
#include <iostream>

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
	return sqrt(d);
}
