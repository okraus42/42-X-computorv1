/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 16:28:55 by okraus            #+#    #+#             */
/*   Updated: 2026/09/29 16:33:53 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //printf

double	my_sqrt(double square);

void	print_discriminant_zero(double a, double b)
{
	printf("Discriminant is zero, the one solutions is:\n");
	printf("%g\n", (-b / (2 * a)));
}

void	print_discriminant_positive(double a, double b, double d)
{
	printf("Discriminant is strictly positive, the two solutions are:\n");
	printf("%g\n", ((-b + my_sqrt(d)) / (2 * a)));
	printf("%g\n", ((-b - my_sqrt(d)) / (2 * a)));
}

void	print_discriminant_negative(double a, double b, double d)
{
	printf("Discriminant is strictly negative");
	printf(", the two complex solutions are:\n");
	printf("%g + %gi\n", (-b / (2 * a)), (my_sqrt(d)) / (2 * a));
	printf("%g - %gi\n", (-b / (2 * a)), (my_sqrt(d)) / (2 * a));
}

void	print_discriminant_nan(void)
{
	printf("Discriminant is not a number, no solution exists\n");
}
