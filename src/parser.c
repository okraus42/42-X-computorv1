/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:05:25 by okraus            #+#    #+#             */
/*   Updated: 2026/09/30 17:08:44 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"
#include <stdlib.h> // strtod, strtol
#include <stdio.h> // dprintf
#include <string.h> // memset

int	log_error(const char *s1, const char *s2, int code);

static int	get_sign(t_parser *parser, int *equal, int *first, t_token *token)
{
	printf("get_sign [%s]\n", &parser->equation[parser->i]);
	// skip space
	while (parser->equation[parser->i] == ' ')
		++(parser->i);
	// if '=' handle if not first
	if (parser->equation[parser->i] == '=')
	{
		if (*equal == -1)
			return (log_error("second '=' not expected", NULL, 1));
		if (*first == 1)
			return (log_error("'=' token too early", NULL, 1));
		if (parser->equation[parser->i + 1] != ' ')
			return (log_error("space  after '=' expected", NULL, 1));
		*equal = -1;
		*first = 1;
		++(parser->i);
	}
	// skip space
	while (parser->equation[parser->i] == ' ')
		++(parser->i);
	// end at end of string
	if (parser->equation[parser->i] == '\0')
	{
		if (*first == 0)
			return (log_error("end of string [%s]\n", &parser->equation[parser->i], 0));
		else
			return (log_error("Unexpected end of string", NULL, 1));
	}
	// find sign
	if (parser->equation[parser->i] == '+' && parser->equation[parser->i + 1] == ' ')
		token->sign = 1;
	else if (parser->equation[parser->i] == '-' && parser->equation[parser->i + 1] == ' ')
		token->sign = -1;
	else if (*first > 0)
		token->sign = 1;
	if (token->sign == 0)
		return (log_error("'+' or '-' expected or not followed by space" , NULL, 1));
	if (parser->equation[parser->i] == '+' || parser->equation[parser->i] == '-')
		++(parser->i);
	if (*first == 1)
		*first = 0;
	return (0);
}

int	get_number(t_parser *parser, t_token *token)
{
	char	*end;

	printf("get_number [%s]\n", &parser->equation[parser->i]);
	// skip space
	while (parser->equation[parser->i] == ' ')
		++(parser->i);
	if (parser->equation[parser->i] == 'X')
	{
		token->value = 1;
		return (0);
	} 
	if (parser->equation[parser->i] < '0' || parser->equation[parser->i] > '9')
		return (log_error("number expected [%s]\n", &parser->equation[parser->i], 1));
	token->value = strtod(&parser->equation[parser->i], &end);
	if (end == &parser->equation[parser->i])
		return (log_error("Error d1 [%s]\n", &parser->equation[parser->i], 1));
	if (token->value >= HUGE_VAL || token->value <= -HUGE_VAL || token->value != token->value)
		return (log_error("Error d2 [%s]\n", &parser->equation[parser->i], 1));
	parser->i = end - parser->equation;
	if (parser->equation[parser->i] == 'X')
		return (0);
	while (parser->equation[parser->i] == ' ')
		++(parser->i);
	if (parser->equation[parser->i] == '*')
		++(parser->i);
	else
		return (log_error("token '*' expected [%s]\n", &parser->equation[parser->i], 1));
	while (parser->equation[parser->i] == ' ')
		++(parser->i);
	return (0);
}


int	get_power(t_parser *parser, t_token *token)
{
	char	*end;

	printf("get_power [%s]\n", &parser->equation[parser->i]);
	if (parser->equation[parser->i] == ' ')
	{
		token->power = 0;
		++(parser->i);
		return (0);
	}
	if (parser->equation[parser->i] == 'X' && parser->equation[parser->i + 1] != '^')
	{
		token->power = 1;
		++(parser->i);
		return (0);
	}
	if (parser->equation[parser->i] == 'X' && parser->equation[parser->i + 1] == '^')
	{
		parser->i += 2;
	}
	if (parser->equation[parser->i] < '0' || parser->equation[parser->i] > '9')
		return (log_error("Error p1 [%s]\n", &parser->equation[parser->i], 1));
	token->power = strtol(&parser->equation[parser->i], &end, 10);
	if (end == &parser->equation[parser->i])
		return (log_error("Error p2 [%s]\n", &parser->equation[parser->i], 1));
	parser->i = end - parser->equation;
	return (0);
}

// "    +   4 * X^2  - 3 X + 2 = 0" // fine
// "    +   4 * X^2  - 3 X + 2 = " // error
int	parse_term(t_parser *parser, int *equal, int *first)
{
	t_token	token;
	int		ret_val;

	memset(&token, 0, sizeof(token));
	//get sign (optional if first = 1)
	ret_val = get_sign(parser, equal, first, &token);
	if (ret_val != 0)
		return (ret_val);
	//get number (if missing but X, it is 1)
	ret_val = get_number(parser, &token);
	if (ret_val != 0)
		return (ret_val);
	//get power (if ^ missing -> 1, if X missing -> 0)
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
	while (return_value == 0 && parser->equation[parser->i] != '\0')
	{
		return_value = parse_term(parser, &equal, &first);
	}
	// printf("[%s] [%i]\n", &parser->equation[parser->i], return_value);
	return (return_value);
}
