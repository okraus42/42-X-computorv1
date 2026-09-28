/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:05:31 by okraus            #+#    #+#             */
/*   Updated: 2026/09/28 17:12:31 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"
#include <stdio.h> //printf

double	my_sqrt(double square);

void	solve_more(t_parser *parser)
{
	printf("Polynomial degree: %i\n", parser->max_power);
	printf("The polynomial degree is strictly greater than 2, I can't solve.\n");
}

void	solve_two(t_parser *parser)
{
	double	a;
	double	b;
	double	c;
	double	d;

	a = parser->left[2].value;
	b = parser->left[1].value;
	c = parser->left[0].value;
	d = b * b - 4 * a * c;
	printf("Polynomial degree: 2\n");
	if (d == 0)
	{
		printf("Discriminant is zero, the one solutions is:\n");
		printf("%g\n", (-b / (2 * a)));
	}
	else if (d > 0)
	{
		printf("Discriminant is strictly positive, the two solutions are:\n");
		printf("%g\n", ((-b + my_sqrt(d)) / (2 * a)));
		printf("%g\n", ((-b - my_sqrt(d)) / (2 * a)));
	}
	else if (d < 0)
	{
		printf("Discriminant is strictly negative, the two complex solutions are:\n");
		printf("%g + %gi\n", (-b / (2 * a)), (my_sqrt(d)) / (2 * a));
		printf("%g - %gi\n", (-b / (2 * a)), (my_sqrt(d)) / (2 * a));
	}
	else
	{
		printf("Discriminant is not a number, no solution exists\n");
	}
}

void	solve_one(t_parser *parser)
{
	double	result;

	result = parser->left[0].value / parser->left[1].value;
	printf("Polynomial degree: 1\n");
	printf("The solution is:\n");
	printf("%g\n", result);
}

void	solve_zero(t_parser *parser)
{
	if (parser->left[0].value == 0)
	{
		printf("Any real number is a solution.\n");
	}
	else
	{
		printf("No solution.\n");
	}
}

void	solve(t_parser *parser)
{
	if (parser->max_power == 0)
	{
		solve_zero(parser);
	}
	else if (parser->max_power == 1)
	{
		solve_one(parser);
	}
	else if (parser->max_power == 2)
	{
		solve_two(parser);
	}
	else
	{
		solve_more(parser);
	}
}
