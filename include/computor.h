/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:05:09 by okraus            #+#    #+#             */
/*   Updated: 2026/09/28 17:06:57 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_H
# define COMPUTOR_H

# include <stdbool.h> // bool

# define MAX_POWER	1024
# define BUFFER_SIZE	4096
# define HUGE_VAL	1e9

typedef struct s_token
{
	double	value;
	int		whole;
	int		fraction;
}	t_token;

typedef struct s_parser
{
	const char	*equation;
	t_token		left[MAX_POWER];
	int			max_power;
	bool		is_right_side;
}	t_parser;

#endif // COMPUTOR_H
