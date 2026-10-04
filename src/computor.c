/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:05:17 by okraus            #+#    #+#             */
/*   Updated: 2026/10/04 11:24:40 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //printf, dprintf
#include <string.h> // memset
#include "computor.h" //t_token

// The str in its reduced form.
// The degree of the str.
// It’s solution(s) and the polarity of the discriminant if it makes sens.

int		parse(t_parser *parser);

void	reduce(t_parser *parser, int i, int sign);

void	solve(t_parser *parser);

int	computor(char const *str)
{
	t_parser	parser;

	if (str == NULL)
	{
		dprintf(2, "Usage:\n");
		return (1);
	}
	memset(&parser, 0, sizeof(parser));
	parser.str = str;
	if (parse(&parser))
		return (1);
	reduce(&parser, 0, 1);
	solve(&parser);
	return (0);
}
