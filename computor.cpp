/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 08:59:23 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/20 17:37:37 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.hpp"

computor::computor(const char *input, int flags) : input(input), flags(flags) {
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
	while (*it && (isdigit(*it) || *it == '.')) {
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

static type get_token_type(char c) {
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
		int col = it - input.cbegin() + 1;
		if (::isalpha(*it)) {
			tokens.emplace_back(extract_identifier(it), col, type::IDENTIFIER);
		} else if (isdigit(*it) || *it == '.') {
			std::string number = extract_number(it);
			if (std::count(number.begin(), number.end(), '.') > 1) {
				error_message = "coefficient `" + number
					+ "` invalid at line 1:" + std::to_string(col);
				tokens.clear();
				return;
			}
			tokens.emplace_back(std::move(number), col, type::NUMBER);
		} else if(is_operator(*it)) {
			tokens.emplace_back(*it, col, get_token_type(*it));
			contains_equal |= tokens.back().get_type() == EQUAL;
			++it;
		} else if (*it == ' '){
			++it;
		} else {
			error_message = "unexpected token `" + extract_unexpected_token(it)
				+ "` at line 1:" + std::to_string(it - input.cbegin());
			tokens.clear();
			return;
		}
	}
	if (!contains_equal) {
		error_message = "invalid equation! equation must contain left and right"
			" hand, no equal detected";
		tokens.clear();
		return;
	}
	tokens.emplace_back(input.size(), type::END);
}

void computor::check_syntax() {
	for (size_t i = 1; i < tokens.size(); ++i) {
		const token &previous = tokens[i - 1];
		const token &current = tokens[i];

		if (!previous.is_token_expected(current)) {
			if (current.get_type() == END) {
				error_message = "unexpected end of equation";
			} else {
				error_message = "unexpected token `" + current.get_value()
					+ "` at line 1:" + std::to_string(current.get_index());
			}
			tokens.clear();
			return;
		}
	}
}

void computor::generate_expressions() {
	size_t i = 1;
	int sign = 1;

	while (i < tokens.size() - 1) {
		if (tokens[i].get_type() == NUMBER) {
			int minus = (tokens[i - 1].get_type() == MINUS ? -1 : 1);
			if (tokens[i + 1].get_type() == END
				|| tokens[i + 1].get_type() == PLUS
				|| tokens[i + 1].get_type() == MINUS
				|| tokens[i + 1].get_type() == EQUAL) {
				expressions.emplace_back(0,
					minus * sign * std::stod(tokens[i].get_value()), "");
			} else if (tokens[i + 1].get_type() == IDENTIFIER) {
				const std::string &identifier = tokens[i + 1].get_value();
				if (!identifier.empty()) {
					identifiers.insert(identifier);
				}
				if (identifiers.size() > 1) {
					error_message = "too many variables";
					break;
				}
				if (tokens[i + 2].get_type() == END
					|| tokens[i + 2].get_type() == PLUS
					|| tokens[i + 2].get_type() == MINUS
					|| tokens[i + 2].get_type() == EQUAL) {
					expressions.emplace_back(1,
						minus * sign * std::stod(tokens[i].get_value()),
						tokens[i + 1].get_value());
					++i;
				} else if (tokens[i + 2].get_type() == POWER) {
					const std::string &pow = tokens[i + 3].get_value();
					if (std::count(pow.begin(), pow.end(), '.') >= 1) {
						error_message = "power `" + pow + "` invalid at line 1:"
							+ std::to_string(tokens[i + 3].get_index() + 1);
						break;
					}
					expressions.emplace_back(std::stoi(tokens[i + 3].get_value()),
						minus * sign * std::stod(tokens[i].get_value()),
						tokens[i + 1].get_value());
					i += 3;
				}
			} else if (tokens[i + 1].get_type() == MULTIPLY) {
				const std::string &identifier = tokens[i + 2].get_value();
				if (!identifier.empty()) {
					identifiers.insert(identifier);
				}
				if (identifiers.size() > 1) {
					error_message = "too many variables";
					break;
				}
				if (tokens[i + 3].get_type() == END
					|| tokens[i + 3].get_type() == PLUS
					|| tokens[i + 3].get_type() == MINUS
					|| tokens[i + 3].get_type() == EQUAL) {
					expressions.emplace_back(1,
						minus * sign * std::stod(tokens[i].get_value()),
						tokens[i + 2].get_value());
					i += 2;
				} else if (tokens[i + 3].get_type() == POWER) {
					const std::string &pow = tokens[i + 4].get_value();
					if (std::count(pow.begin(), pow.end(), '.') >= 1) {
						error_message = "power `" + pow + "` invalid at line 1:"
							+ std::to_string(tokens[i + 4].get_index() + 1);
						break;
					}
					expressions.emplace_back(std::stoi(tokens[i + 4].get_value()),
						minus * sign * std::stod(tokens[i].get_value()),
						tokens[i + 2].get_value());
					i += 4;
				}
			}
		} else if (tokens[i].get_type() == IDENTIFIER) {
			int minus = (tokens[i - 1].get_type() == MINUS ? -1 : 1);
			const std::string &identifier = tokens[i].get_value();
			if (!identifier.empty()) {
				identifiers.insert(identifier);
			}
			if (identifiers.size() > 1) {
				error_message = "too many variables";
				break;
			}
			if (tokens[i + 1].get_type() == END
				|| tokens[i + 1].get_type() == PLUS
				|| tokens[i + 1].get_type() == MINUS
				|| tokens[i + 1].get_type() == EQUAL) {
				expressions.emplace_back(1,
					minus * sign * 1.0, tokens[i].get_value());
			} else if (tokens[i + 1].get_type() == POWER) {
				const std::string &pow = tokens[i + 2].get_value();
				if (std::count(pow.begin(), pow.end(), '.') >= 1) {
					error_message = "power `" + pow + "` invalid at line 1:"
						+ std::to_string(tokens[i + 2].get_index() + 1);
					break;
				}
				expressions.emplace_back(std::stoi(tokens[i + 2].get_value()),
					minus * sign * 1.0, tokens[i].get_value());
				i += 2;
			}
		} else if (tokens[i].get_type() == EQUAL) {
			sign = -1;
		}
		++i;
	}
}

void computor::reduce_expressions() {
	std::vector<expression> exps;
	size_t i = 1;

	std::sort(expressions.begin(), expressions.end(),
		[](const expression &exp1, const expression &exp2) {
			return exp1.get_degree() < exp2.get_degree();
		});

	double c = expressions[0].get_coefficient();
	std::string variable = identifiers.empty() ? "X" : *identifiers.begin();
	while (i < expressions.size()) {
		if (expressions[i].get_degree() == expressions[i - 1].get_degree()) {
			c += expressions[i].get_coefficient();
		} else {
			if (c != 0) {
				exps.emplace_back(expressions[i - 1].get_degree(), c, variable);
			}
			c = expressions[i].get_coefficient();
		}
		++i;
	}
	if (c != 0) {
		exps.emplace_back(expressions.back().get_degree(), c, variable);
	}
	std::swap(exps, expressions);
	exps.clear();
}

void computor::compile() {
	if (flags & F_VERBOSE) {
		std::cout << "Parsing input..." << std::endl;
	}
	parse();
	if (flags & F_VERBOSE) {
		std::cout << "Parsing input...done" << std::endl;
	}
	if (is_malformed_input()) {
		return;
	}

	if (flags & F_VERBOSE) {
		std::cout << "Checking syntax..." << std::endl;
	}
	check_syntax();
	if (is_malformed_input()) {
		return;
	}
	if (flags & F_VERBOSE) {
		std::cout << "Checking syntax...done" << std::endl;
	}

	if (flags & F_VERBOSE) {
		std::cout << "Generating expressions from equation..." << std::endl;
	}
	try {
		generate_expressions();
	} catch (const std::out_of_range &e) {
		error_message = "number too large";
	}
	if (is_malformed_input()) {
		expressions.clear();
		tokens.clear();
		identifiers.clear();
		return;
	}
	if (flags & F_VERBOSE) {
		std::cout << "Generating expressions from equation...done" << std::endl;
	}
	if (flags & F_VERBOSE) {
		std::cout << "Reducing expressions..." << std::endl;
	}
	reduce_expressions();
	if (flags & F_VERBOSE) {
		std::cout << "Reducing expressions...done" << std::endl;
	}
}

void computor::evaluate() {
	if (expressions.size() == 0) {
		std::cout << "Reduced form: 0 = 0" << std::endl;
		std::cout << "Polynomial degree: 0" << std::endl;
		std::cout << "The equation has infinite solutions" << std::endl;
		return;
	} else if (expressions.size() == 1 && expressions.back().get_degree() == 0) {
		std::cout << "Reduced form: " << get_reduced_form() << std::endl;
		std::cout << "Polynomial degree: 0" << std::endl;
		std::cout << "The equation has no solutions" << std::endl;
		return;
	} else if (expressions.back().get_degree() >= 3) {
		std::cout << "Reduced form: " << get_reduced_form() << std::endl;
		std::cout << "Polynomial degree: " << expressions.back().get_degree()
			<< std::endl;
		std::cout << "The polynomial degree is strictly greater than 2,"
			" I can't solve." << std::endl;
		return;
	} else if (expressions.back().get_degree() == 1) {
		std::cout << "Reduced form: " << get_reduced_form() << std::endl;
		std::cout << "Polynomial degree: 1" << std::endl;
		std::cout << "The solution is:" << std::endl;
		if (expressions.size() == 1) {
			std::cout << "0" << std::endl;
		} else {
			std::cout << (-(double)expressions.front().get_coefficient()
				/ expressions.back().get_coefficient()) << std::endl;
		}
		return;
	}
	std::cout << "Reduced form: " << get_reduced_form() << std::endl;
	std::cout << "Polynomial degree: " << expressions.back().get_degree()
		<< std::endl;
	double a = expressions.back().get_coefficient();
	double b = 0;
	double c = 0;
	if (expressions.size() == 2) {
		b = expressions.front().get_degree() == 1 ?
			expressions.front().get_coefficient() : 0;
		c = expressions.front().get_degree() == 0 ?
			expressions.front().get_coefficient() : 0;
	} else if (expressions.size() == 3) {
		b = expressions[1].get_coefficient();
		c = expressions[0].get_coefficient();
	}
	double delta = b * b - 4 * a * c;
	if (delta == 0) {
		std::cout << "Discriminant is 0, the solution is:" << std::endl;
		std::cout << (-b / 2.0 * a) << std::endl;
	} else if (delta > 0) {
		std::cout << "Discriminant is strictly positive,"
			" the two solutions are:" << std::endl;
		double root = my_sqrt(delta);
		std::cout << ((-b - root) / (2.0 * a)) << std::endl;
		std::cout << ((-b + root) / (2.0 * a)) << std::endl;
	} else {
		double root = my_sqrt(delta);
		std::cout << "Discriminant is strictly negative,"
			" the two complex solutions are:" << std::endl;
		std::cout << (-b/ (2.0 * a)) << " + " << (root / (2.0 * a))
			<< "i" << std::endl;
		std::cout << (-b/ (2.0 * a)) << " - " << (root / (2.0 * a))
			<< "i" << std::endl;
	}
}

std::string computor::get_reduced_form() const {
	std::stringstream string_builder;

	for (size_t i = 0; i < expressions.size(); ++i) {
		const expression &exp = expressions[i];
		if (i != 0) {
			string_builder << (exp.get_coefficient() >= 0 ? " + " : " ");
		}
		if (!(flags & F_NATURAL)) {
			string_builder << exp.get_coefficient() << " * "
				<< exp.get_variable() << " ^ " << exp.get_degree();
		} else {
			if (exp.get_coefficient() == 1) {
				if (exp.get_degree() >= 1) {
					string_builder << exp.get_variable();
					if (exp.get_degree() >= 2) {
						string_builder << " ^ " << exp.get_degree();
					}
				} else {
					string_builder << "1";
				}
			} else if (exp.get_coefficient() == -1) {
				string_builder << "-";
				if (exp.get_degree() >= 1) {
					string_builder << exp.get_variable();
					if (exp.get_degree() >= 2) {
						string_builder << " ^ " << exp.get_degree();
					}
				} else {
					string_builder << "1";
				}
			} else {
				string_builder << exp.get_coefficient();
				if (exp.get_degree() >= 1) {
					string_builder << " * " << exp.get_variable();
					if (exp.get_degree() >= 2) {
						string_builder << " ^ " << exp.get_degree();
					}
				}
			}
		}
	}
	string_builder << " = 0";

	return string_builder.str();
}
