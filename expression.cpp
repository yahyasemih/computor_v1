/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:09:55 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/17 23:23:50 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expression.hpp"

expression::expression(int degree, double coefficient, const std::string &variable)
		: degree(degree), coefficient(coefficient), variable(variable) {}

int expression::get_degree() const {
	return degree;
}

double expression::get_coefficient() const {
	return coefficient;
}

const std::string &expression::get_variable() const {
	return variable;
}
