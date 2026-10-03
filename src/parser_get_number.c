/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_number.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:05:25 by okraus            #+#    #+#             */
/*   Updated: 2026/10/02 17:25:42 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"
#include <stdlib.h> // strtod
#include <stdio.h> // printf

int	log_error(const char *s1, const char *s2, int code);

static int	handle_end(t_parser *parser)
{
	if (parser->str[parser->i] == 'X')
		return (0);
	while (parser->str[parser->i] == ' ')
		++(parser->i);
	if (parser->str[parser->i] == '*')
		++(parser->i);
	else
		return (log_error("token '*' expected [%s]\n",
				&parser->str[parser->i], 1));
	while (parser->str[parser->i] == ' ')
		++(parser->i);
	return (0);
}

int	get_number(t_parser *parser, t_token *token)
{
	char	*end;

	while (parser->str[parser->i] == ' ')
		++(parser->i);
	if (parser->str[parser->i] == 'X')
	{
		token->value = 1;
		return (0);
	}
	if (parser->str[parser->i] < '0' || parser->str[parser->i] > '9')
		return (log_error("number expected [%s]\n",
				&parser->str[parser->i], 1));
	token->value = strtod(&parser->str[parser->i], &end);
	if (end == &parser->str[parser->i])
		return (log_error("Error d1 [%s]\n", &parser->str[parser->i], 1));
	if (token->value >= HUGE_VAL || token->value <= -HUGE_VAL
		|| token->value != token->value)
		return (log_error("Error d2 [%s]\n", &parser->str[parser->i], 1));
	parser->i = end - parser->str;
	return (handle_end(parser));
}
