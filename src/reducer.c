/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reducer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:05:29 by okraus            #+#    #+#             */
/*   Updated: 2026/10/04 11:31:44 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"
#include <stdio.h> //printf

static void	print_term(t_parser *parser, int *i, int *sign)
{
	printf("%g * X^%i", parser->left[*i].value * (*sign), *i);
	(*i)++;
	if (*i <= parser->max_power)
	{
		if (parser->left[*i].value < 0)
		{
			*sign = -1;
			printf(" - ");
		}
		else
		{
			*sign = 1;
			printf(" + ");
		}
	}
}

void	reduce(t_parser *parser)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	printf("Reduced form: ");
	while (i <= parser->max_power)
	{
		if (parser->left[i].value == 0.0)
		{
			++i;
			continue ;
		}
		print_term(parser, &i, &sign);
	}
	printf(" = 0\n");
}
