/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 08:59:28 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/18 19:09:09 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_HPP
#define COMPUTOR_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <sstream>
#include "expression.hpp"
#include "token.hpp"
#include "utilities.hpp"

class computor {
private:
	std::vector<token> tokens;
	std::vector<expression> expressions;
	const std::string input;
	std::string error_message;

	void parse();
	std::string get_reduced_form() const;
public:
	computor(const computor &other) = delete;
	computor(computor &&other) = delete;

	computor &operator=(const computor &other) = delete;
	computor &operator=(computor &&other) = delete;

	computor(const char *input);
	~computor() = default;

	bool is_malformed_input() const { return !error_message.empty(); }
	const std::string &get_error_message() const { return error_message; }
	const std::vector<expression> &get_result() const { return expressions; }

	void compile();
	void evaluate();
};

#endif // COMPUTOR_HPP
