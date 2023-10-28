/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:40:55 by ael-maar          #+#    #+#             */
/*   Updated: 2023/10/28 13:47:09 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <ctime>

// time_t str_to_timestamp(const std::string &dateStr);
// bool is_valid_input(const std::string &input);

bool isNumeric(const std::string &str);
double strToDouble(const std::string &input);

#endif
