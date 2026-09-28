/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:05:17 by okraus            #+#    #+#             */
/*   Updated: 2026/09/28 17:07:59 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //printf, dprintf
#include <string.h> // memset
#include "computor.h" //t_token

// The equation in its reduced form.
// The degree of the equation.
// It’s solution(s) and the polarity of the discriminant if it makes sens.

int		parse(t_parser *parser);

void	reduce(t_parser *parser);

void	solve(t_parser *parser);

int	computor(char const *equation)
{
	t_parser	parser;

	if (equation == NULL)
	{
		dprintf(2, "Usage:\n");
		return (1);
	}
	memset(&parser, 0, sizeof(parser));
	printf("The equation is: %s\n", equation);
	parser.equation = equation;
	if (parse(&parser))
		return (1);
	reduce(&parser);
	solve(&parser);
	return (0);
}
