/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 08:59:28 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/18 21:25:51 by yez-zain         ###   ########.fr       */
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

#define F_VERBOSE 1
#define F_NORMAL 2

class computor {
private:
	const std::string input;
	int flags;
	std::vector<token> tokens;
	std::vector<expression> expressions;
	std::string error_message;
	std::unordered_set<std::string> identifiers;

	void parse();
	void check_syntax();
	void generate_expressions();
	void reduce_expressions();
	std::string get_reduced_form() const;
public:
	computor(const computor &other) = delete;
	computor(computor &&other) = delete;

	computor &operator=(const computor &other) = delete;
	computor &operator=(computor &&other) = delete;

	computor(const char *input, int flags = 0);
	~computor() = default;

	bool is_malformed_input() const { return !error_message.empty(); }
	const std::string &get_error_message() const { return error_message; }
	const std::vector<expression> &get_result() const { return expressions; }

	void compile();
	void evaluate();
};

#endif // COMPUTOR_HPP
