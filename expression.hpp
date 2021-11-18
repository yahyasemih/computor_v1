/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:06:17 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/17 23:23:44 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>

class expression {
private:
	int degree;
	double coefficient;
	std::string variable;
public:
	expression(int degree, double coefficient, const std::string &variable);
	~expression() = default;

	int get_degree() const;
	double get_coefficient() const;
	const std::string &get_variable() const;
};

#endif // EXPRESSION_HPP
