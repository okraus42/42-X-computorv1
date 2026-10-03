/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:05:25 by okraus            #+#    #+#             */
/*   Updated: 2026/10/02 17:15:17 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"
#include <string.h> // memset

int	get_sign(t_parser *parser, int *equal, int *first, t_token *token);
int	get_number(t_parser *parser, t_token *token);
int	get_power(t_parser *parser, t_token *token);
int	log_error(const char *s1, const char *s2, int code);

int	parse_term(t_parser *parser, int *equal, int *first)
{
	t_token	token;
	int		ret_val;

	memset(&token, 0, sizeof(token));
	ret_val = get_sign(parser, equal, first, &token);
	if (ret_val != 0)
		return (ret_val);
	ret_val = get_number(parser, &token);
	if (ret_val != 0)
		return (ret_val);
	ret_val = get_power(parser, &token);
	if (ret_val != 0)
		return (ret_val);
	if (parser->max_power < token.power)
		parser->max_power = token.power;
	parser->left[token.power].value += token.value * token.sign * (*equal);
	return (0);
}

int	parse(t_parser *parser)
{
	int	return_value;
	int	equal;
	int	first;

	return_value = 0;
	equal = 1;
	first = 1;
	while (return_value == 0 && parser->str[parser->i] != '\0')
	{
		return_value = parse_term(parser, &equal, &first);
	}
	if (equal == 1 && return_value == 0)
		return (log_error("'=' expected", NULL, 1));
	return (return_value);
}
