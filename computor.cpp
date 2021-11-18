/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 08:59:23 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/18 01:34:49 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"

computor::computor(const char *input) : input(input) {
}

std::string extract_identifier(std::string::const_iterator &it) {
	std::string::const_iterator it2 = it;
	while (*it && isalpha(*it)) {
		++it;
	}
	std::string value;
	value.reserve(it - it2);
	std::copy(it2, it, std::back_inserter(value));
	return value;
}

std::string extract_number(std::string::const_iterator &it) {
	std::string::const_iterator it2 = it;
	while (*it && isdigit(*it)) {
		++it;
	}
	std::string value;
	value.reserve(it - it2);
	std::copy(it2, it, std::back_inserter(value));
	return value;
}

std::string extract_unexpected_token(std::string::const_iterator &it) {
	std::string::const_iterator it2 = it;
	while (*it && *it != ' ') {
		++it;
	}
	std::string value;
	value.reserve(it - it2);
	std::copy(it2, it,  std::back_inserter(value));
	return value;
}

type get_token_type(char c) {
	if (c == '=') {
		return EQUAL;
	} else if (c == '+') {
		return PLUS;
	} else if (c == '-') {
		return MINUS;
	} else if (c == '*') {
		return MULTIPLY;
	} else if (c == '^') {
		return POWER;
	} else {
		return INVALID;
	}
}

void computor::parse() {
	tokens.emplace_back(input.size(), type::START);
	bool contains_equal = false;
	std::string::const_iterator it = input.cbegin();
	while (it != input.cend()) {
		int column = it - input.cbegin() + 1;
		if (::isalpha(*it)) {
			tokens.emplace_back(extract_identifier(it), column, type::IDENTIFIER);
		} else if (isdigit(*it)) {
			tokens.emplace_back(extract_number(it), column, type::NUMBER);
		} else if(is_operator(*it)) {
			tokens.emplace_back(*it, column, get_token_type(*it));
			contains_equal |= tokens.back().get_type() == EQUAL;
			++it;
		} else if (*it == ' '){
			++it;
		} else {
			error_message = "unexpected token `" + extract_unexpected_token(it) + "` at line 1:" + std::to_string(it - input.cbegin());
			tokens.clear();
			return;
		}
	}
	if (!contains_equal) {
		error_message = "invalid equation! equation must contain left and right hand, no equal detected";
		tokens.clear();
		return;
	}
	tokens.emplace_back(input.size(), type::END);
}

void computor::compile() {
	parse();
	if (is_malformed_input()) {
		return;
	}

	for (int i = 1; i < tokens.size(); ++i) {
		const token &previous = tokens[i - 1];
		const token &current = tokens[i];

		if (!previous.is_token_expected(current)) {
			if (current.get_type() == END) {
				error_message = "unexpected end of equation";
			} else {
				error_message = "unexpected token `" + current.get_value() + "` at line 1:" + std::to_string(current.get_index());
			}
			break;
		}
	}

	int i = 1;
	int sign = 1;
	std::unordered_set<std::string> identifiers;
	while (i < tokens.size() - 1) {
		if (tokens[i].get_type() == NUMBER) {
			int minus_coefficient = (i > 0 && tokens[i - 1].get_type() == MINUS ? -1 : 1);
			if (tokens[i + 1].get_type() == END || tokens[i + 1].get_type() == PLUS || tokens[i + 1].get_type() == MINUS || tokens[i + 1].get_type() == EQUAL) {
				expressions.emplace_back(0, minus_coefficient * sign * std::stod(tokens[i].get_value()), "");
			} else if (tokens[i + 1].get_type() == IDENTIFIER) {
				const std::string &identifier = tokens[i + 1].get_value();
				if (!identifier.empty()) {
					identifiers.insert(identifier);
				}
				if (identifiers.size() > 1) {
					error_message = "Too many variable names";
					break;
				}
				if (tokens[i + 2].get_type() == END || tokens[i + 2].get_type() == PLUS || tokens[i + 2].get_type() == MINUS || tokens[i + 2].get_type() == EQUAL) {
					expressions.emplace_back(1, minus_coefficient * sign * std::stod(tokens[i].get_value()), tokens[i + 1].get_value());
					++i;
				} else if (tokens[i + 2].get_type() == POWER) {
					expressions.emplace_back(std::stoi(tokens[i + 3].get_value()), minus_coefficient * sign * std::stod(tokens[i].get_value()), tokens[i + 1].get_value());
					i += 3;
				}
			} else if (tokens[i + 1].get_type() == MULTIPLY) {
				if (tokens[i + 3].get_type() == END || tokens[i + 3].get_type() == PLUS || tokens[i + 3].get_type() == MINUS || tokens[i + 3].get_type() == EQUAL) {
					expressions.emplace_back(1, minus_coefficient * sign * std::stod(tokens[i].get_value()), tokens[i + 2].get_value());
					i += 2;
				} else if (tokens[i + 3].get_type() == POWER) {
					expressions.emplace_back(std::stoi(tokens[i + 4].get_value()), minus_coefficient * sign * std::stod(tokens[i].get_value()), tokens[i + 2].get_value());
					i += 4;
				}
			}
		} else if (tokens[i].get_type() == IDENTIFIER) {
			int minus_coefficient = (i > 0 && tokens[i - 1].get_type() == MINUS ? -1 : 1);
			const std::string &identifier = tokens[i].get_value();
			if (!identifier.empty()) {
				identifiers.insert(identifier);
			}
			if (identifiers.size() > 1) {
				error_message = "Too many variable names";
				break;
			}
			if (tokens[i + 1].get_type() == END || tokens[i + 1].get_type() == PLUS || tokens[i + 1].get_type() == MINUS || tokens[i + 1].get_type() == EQUAL) {
					expressions.emplace_back(1, minus_coefficient * sign * 1.0, tokens[i].get_value());
				} else if (tokens[i + 1].get_type() == POWER) {
					expressions.emplace_back(std::stoi(tokens[i + 2].get_value()), minus_coefficient * sign * 1.0, tokens[i].get_value());
					i += 2;
				}
		} else if (tokens[i].get_type() == EQUAL) {
			sign = -1;
		}
		++i;
	}
	if (is_malformed_input()) {
		expressions.clear();
		tokens.clear();
		identifiers.clear();
	}

	std::sort(expressions.begin(), expressions.end(),
		[](const expression &exp1, const expression &exp2) {
			return exp1.get_degree() < exp2.get_degree();
		});

	std::vector<expression> exps;
	i = 1;
	double c = expressions[0].get_coefficient();
	std::string variable = identifiers.empty() ? "X" : *identifiers.begin();
	while (i < expressions.size()) {
		if (expressions[i].get_degree() == expressions[i - 1].get_degree()) {
			c += expressions[i].get_coefficient();
		} else {
			std::cout << "====> c is " << c << std::endl;
			if (c != 0) {
				exps.emplace_back(expressions[i - 1].get_degree(), c, variable);
			}
			c = expressions[i].get_coefficient();
		}
		++i;
	}
	std::cout << "====> c is " << c << std::endl;
	if (c != 0) {
		exps.emplace_back(expressions.back().get_degree(), c, variable);
	}
	std::swap(exps, expressions);
	exps.clear();
}
