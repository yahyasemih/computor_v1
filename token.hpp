/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:57:56 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/18 00:58:59 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum type {
	IDENTIFIER,
	NUMBER,
	PLUS,
	MINUS,
	MULTIPLY,
	POWER,
	EQUAL,
	END,
	START,
	INVALID
};

class token {
private:
	const std::string value;
	const int index;
	const type token_type;
public:
	token() = delete;

	token(const std::string &value, int index, type token_type);
	token(char value, int index, type token_type);
	token(int index, type token_type); // for some types of tokens (space, equal)
	token(std::string &&value, int index, type token_type);
	~token() = default;

	const std::string &get_value() const { return value; }
	const int get_index() const { return index; }
	const type get_type() const { return token_type; }

	bool is_token_expected(const token &other) const;
};

#endif // TOKEN_HPP
