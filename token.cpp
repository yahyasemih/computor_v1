/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 20:01:17 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/18 00:59:44 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.hpp"

token::token(const std::string &value, int index, type token_type)
		: value(value), index(index), token_type(token_type) {
}

token::token(char value, int index, type token_type)
		: value(1, value), index(index), token_type(token_type) {
}

token::token(int index, type token_type)
		: index(index), token_type(token_type) {
}

token::token(std::string &&value, int index, type token_type)
		: value(std::move(value)), index(index), token_type(token_type) {
}

bool token::is_token_expected(const token &other) const {
	if (other.token_type == INVALID || this->token_type == END) {
		return false;
	}

	switch (this->token_type) {
		case START:
			return other.token_type == NUMBER
				|| other.token_type == MINUS
				|| other.token_type == IDENTIFIER;
		case NUMBER:
			return other.token_type == EQUAL
				|| other.token_type == IDENTIFIER
				|| other.token_type == END
				|| other.token_type == MULTIPLY
				|| other.token_type == PLUS
				|| other.token_type == MINUS;
		case IDENTIFIER:
			return other.token_type == PLUS
				|| other.token_type == MINUS
				|| other.token_type == END
				|| other.token_type == POWER
				|| other.token_type == EQUAL;
		case POWER:
			return other.token_type == NUMBER;
		case MULTIPLY:
			return other.token_type == IDENTIFIER;
		case PLUS:
		case MINUS:
			return other.token_type == IDENTIFIER
				|| other.token_type == NUMBER;
		case EQUAL:
			return other.token_type == NUMBER
				|| other.token_type == IDENTIFIER
				|| other.token_type == MINUS;
		default:
			return false;
	}

	return false;
}
