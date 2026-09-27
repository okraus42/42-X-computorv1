#pragma once
#ifndef COMPUTOR_H
# define COMPUTOR_H

#include <stdbool.h> // bool

#define MAX_POWER	1024
#define BUFFER_SIZE	4096
#define HUGE_VAL	1e9

typedef struct s_token {
	double	value;
	int		whole;
	int		fraction;
} t_token;

typedef struct s_parser {
	const char	*equation;
	t_token		left[MAX_POWER];
	int			max_power;
	bool		is_right_side;
}	t_parser;

#endif // COMPUTOR_H
