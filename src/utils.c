/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:05:33 by okraus            #+#    #+#             */
/*   Updated: 2026/09/28 17:11:17 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

double	my_sqrt(double square)
{
	double	guess;
	double	next;
	int		failsafe;

	if (square != square || square == 0)
		return (square);
	if (square < 0)
		square *= -1;
	guess = square;
	failsafe = 0;
	next = 0.5 * (guess + square / guess);
	while (guess != next && failsafe < 64)
	{
		guess = next;
		next = 0.5 * (guess + square / guess);
		failsafe++;
	}
	return (guess);
}
