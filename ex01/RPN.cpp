/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:56:20 by ael-maar          #+#    #+#             */
/*   Updated: 2023/10/29 15:38:10 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool    isoperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void    error(void)
{
    std::cout << "Error" << std::endl;
    exit(EXIT_FAILURE);
}

void calculate(std::stack<int> &st, char op)
{
    if (st.size() < 2)
        error();
    int secondNum = st.top();
    st.pop();
    int firstNum = st.top();
    st.pop();

    switch (op)
    {
        case '+':
            st.push(firstNum + secondNum);
            break;
        case '-':
            st.push(firstNum - secondNum);
            break;
        case '*':
            st.push(firstNum * secondNum);
            break;
        default:
            st.push(firstNum / secondNum);
            break;
    }
}

int    execute(const std::string &expression)
{
    std::stack<int> st;

    for (size_t i = 0; i < expression.length(); i++)
    {
        if (isspace(expression[i]))
            continue;
        if (!isdigit(expression[i]) && !isoperator(expression[i])) // characters other then
            error();
        if ((isdigit(expression[i]) || isoperator(expression[i])) 
        && (!isspace(expression[i + 1]) && expression[i + 1] != '\0')) // digits and operator should not follow by another character
            error();
        if (isdigit(expression[i]))
            st.push(static_cast<int>(expression[i]) - 48);
        else
            calculate(st, expression[i]);
    }
    if (st.size() != 1)
        error();
    return st.top();
}
