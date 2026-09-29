/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:05:31 by okraus            #+#    #+#             */
/*   Updated: 2026/09/29 16:34:28 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"
#include <stdio.h> //printf

void	print_discriminant_zero(double a, double b);
void	print_discriminant_positive(double a, double b, double d);
void	print_discriminant_negative(double a, double b, double d);
void	print_discriminant_nan(void);

void	solve_more(t_parser *parser)
{
	printf("Polynomial degree: %i\n", parser->max_power);
	printf("The polynomial degree is strictly greater than 2");
	printf(", I can't solve.\n");
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
		print_discriminant_zero(a, b);
	else if (d > 0)
		print_discriminant_positive(a, b, d);
	else if (d < 0)
		print_discriminant_negative(a, b, d);
	else
		print_discriminant_nan();
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
