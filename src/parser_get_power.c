/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_power.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:05:25 by okraus            #+#    #+#             */
/*   Updated: 2026/10/02 17:27:45 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"
#include <stdlib.h> // strtol
#include <stdio.h> // printf

int	log_error(const char *s1, const char *s2, int code);

static int	handle_start(t_parser *parser, t_token *token)
{
	if (parser->str[parser->i] == ' ')
	{
		token->power = 0;
		++(parser->i);
		return (0);
	}
	if (parser->str[parser->i] == 'X' && parser->str[parser->i + 1] != '^')
	{
		token->power = 1;
		++(parser->i);
		return (0);
	}
	if (parser->str[parser->i] == 'X' && parser->str[parser->i + 1] == '^')
	{
		parser->i += 2;
	}
	return (1);
}

int	get_power(t_parser *parser, t_token *token)
{
	char	*end;

	printf("get_power [%s]\n", &parser->str[parser->i]);
	if (handle_start(parser, token) == 0)
		return (0);
	if (parser->str[parser->i] < '0' || parser->str[parser->i] > '9')
		return (log_error("Error p1 [%s]\n", &parser->str[parser->i], 1));
	token->power = strtol(&parser->str[parser->i], &end, 10);
	if (end == &parser->str[parser->i])
		return (log_error("Error p2 [%s]\n", &parser->str[parser->i], 1));
	parser->i = end - parser->str;
	return (0);
}
