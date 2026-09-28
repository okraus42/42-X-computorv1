/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:05:25 by okraus            #+#    #+#             */
/*   Updated: 2026/09/28 17:13:32 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"
#include <stdlib.h> // strtod, strtol
#include <stdio.h> // dprintf

int	parse(t_parser *parser)
{
	int		i;
	int		j;
	int		first;
	int		sign;
	double	d;
	long	power;
	char	*end;

	i = 0;
	first = 0;
	sign = 1;
	while (parser->equation[i])
	{
		while (parser->equation[i] == ' ')
			++i;
		if (parser->equation[i] == '-')
		{
			sign = -1;
			i++;
		}
		else if (parser->equation[i] == '+')
		{
			sign = 1;
			i++;
		}
		else if (first != 0 && parser->equation[i] != '=')
		{
			dprintf(2, "Error +/- [%s]\n", &parser->equation[i]);
			return (1);
		}
		while (parser->equation[i] == ' ')
			++i;
		if (parser->equation[i] == '=')
			break ;
		d = strtod(&parser->equation[i], &end);
		if (end == &parser->equation[i])
		{
			dprintf(2, "Error d1 [%s]\n", &parser->equation[i]);
			return (1);
		}
		if (d >= HUGE_VAL || d <= -HUGE_VAL || d != d)
		{
			dprintf(2, "Error d2\n");
			return (1);
		}
		i = end - parser->equation;
		d *= sign;
		while (parser->equation[i] == ' ')
			++i;
		if (parser->equation[i] != '*')
		{
			dprintf(2, "Error *\n");
			return (1);
		}
		++i;
		while (parser->equation[i] == ' ')
			++i;
		if (parser->equation[i] != 'X'
			|| parser->equation[i + 1] != '^'
			|| parser->equation[i + 2] < '0'
			|| parser->equation[i + 2] > '9')
		{
			dprintf(2, "Error X^ [%s]\n", &parser->equation[i]);
			return (1);
		}
		i += 2;
		power = strtol(&parser->equation[i], &end, 10);
		if (end == &parser->equation[i])
		{
			dprintf(2, "Error power1\n");
			return (1);
		}
		i = end - parser->equation;
		if (power < 0 || power >= MAX_POWER)
		{
			dprintf(2, "Error power2\n");
			return (1);
		}
		parser->left[power].value += d;
		if (parser->max_power < power)
			parser->max_power = power;
		while (parser->left[parser->max_power].value == 0.0
			&& parser->max_power > 0)
			parser->max_power -= 1;
		while (parser->equation[i] == ' ')
			++i;
		first = 1;
	}
	if (parser->equation[i] != '=')
	{
		dprintf(2, "Error: %s\n", parser->equation);
		j = -6;
		while (j++ < i)
			dprintf(2, " ");
		dprintf(2, "^ ");
		while (j++ < i)
			dprintf(2, " ");
		dprintf(2, "Equal sign ('=') expected\n");
		return (1);
	}
	i++;
	first = 0;
	sign = 1;
	while (parser->equation[i])
	{
		while (parser->equation[i] == ' ')
			++i;
		if (parser->equation[i] == '-')
		{
			sign = -1;
			i++;
		}
		else if (parser->equation[i] == '+')
		{
			sign = 1;
			i++;
		}
		else if (first != 0 && parser->equation[i] != '=')
		{
			dprintf(2, "Error +/- [%s]\n", &parser->equation[i]);
			return (1);
		}
		while (parser->equation[i] == ' ')
			++i;
		if (parser->equation[i] == '=')
		{
			dprintf(2, "Error = [%s]\n", &parser->equation[i]);
			return (1);
		}
		d = strtod(&parser->equation[i], &end);
		if (end == &parser->equation[i])
		{
			dprintf(2, "Error d1 [%s]\n", &parser->equation[i]);
			return (1);
		}
		if (d >= HUGE_VAL || d <= -HUGE_VAL || d != d)
		{
			dprintf(2, "Error d2\n");
			return (1);
		}
		i = end - parser->equation;
		d *= sign;
		while (parser->equation[i] == ' ')
			++i;
		if (parser->equation[i] != '*')
		{
			dprintf(2, "Error *\n");
			return (1);
		}
		++i;
		while (parser->equation[i] == ' ')
			++i;
		if (parser->equation[i] != 'X'
			|| parser->equation[i + 1] != '^'
			|| parser->equation[i + 2] < '0'
			|| parser->equation[i + 2] > '9')
		{
			dprintf(2, "Error X^ [%s]\n", &parser->equation[i]);
			return (1);
		}
		i += 2;
		power = strtol(&parser->equation[i], &end, 10);
		if (end == &parser->equation[i])
		{
			dprintf(2, "Error power1\n");
			return (1);
		}
		i = end - parser->equation;
		if (power < 0 || power >= MAX_POWER)
		{
			dprintf(2, "Error power2\n");
			return (1);
		}
		parser->left[power].value -= d;
		if (parser->max_power < power)
			parser->max_power = power;
		while (parser->left[parser->max_power].value == 0.0
			&& parser->max_power > 0)
			parser->max_power -= 1;
		while (parser->equation[i] == ' ')
			++i;
		first = 1;
	}
	return (0);
}
