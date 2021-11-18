/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yez-zain <yez-zain@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:29:33 by yez-zain          #+#    #+#             */
/*   Updated: 2021/11/17 14:10:41 by yez-zain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <algorithm>

bool is_number(const std::string &str);
bool is_operator(char c);
bool is_identifier(const std::string &str);

#endif // UTILITIES_HPPß
