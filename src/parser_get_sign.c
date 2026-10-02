/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_sign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:05:25 by okraus            #+#    #+#             */
/*   Updated: 2026/10/02 17:23:02 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"
#include <stdio.h> // printf

int	log_error(const char *s1, const char *s2, int code);

static int	handle_start(t_parser *parser, int *equal, int *first)
{
	while (parser->str[parser->i] == ' ')
		++(parser->i);
	if (parser->str[parser->i] == '=')
	{
		if (*equal == -1)
			return (log_error("second '=' not expected", NULL, 1));
		if (*first == 1)
			return (log_error("'=' token too early", NULL, 1));
		if (parser->str[parser->i + 1] != ' ')
			return (log_error("space  after '=' expected", NULL, 1));
		*equal = -1;
		*first = 1;
		++(parser->i);
	}
	while (parser->str[parser->i] == ' ')
		++(parser->i);
	return (0);
}

int	get_sign(t_parser *parser, int *equal, int *first, t_token *token)
{
	int	return_value;

	return_value = handle_start(parser, equal, first);
	if (return_value != 0)
		return (return_value);
	if (parser->str[parser->i] == '\0')
	{
		if (*first == 0)
			return (0);
		else
			return (log_error("Unexpected end of string", NULL, 1));
	}
	if (parser->str[parser->i] == '+' && parser->str[parser->i + 1] == ' ')
		token->sign = 1;
	else if (parser->str[parser->i] == '-' && parser->str[parser->i + 1] == ' ')
		token->sign = -1;
	else if (*first > 0)
		token->sign = 1;
	if (token->sign == 0)
		return (log_error("sign missing or not followed by space", NULL, 1));
	if (parser->str[parser->i] == '+' || parser->str[parser->i] == '-')
		++(parser->i);
	if (*first == 1)
		*first = 0;
	return (0);
}
