#pragma once
#ifndef COMPUTOR_H
# define COMPUTOR_H

#define LEFT_SIZE 1024
#define RIGHT_SIZE 256
#define BUFFER_SIZE 4096

typedef struct s_token {
	int degree;
	int value;
} t_token;

typedef struct s_parser {
	const char	*equation;
	t_token		left[LEFT_SIZE];
	t_token		right[RIGHT_SIZE];
	int			left_count;
	int			right_count;
}	t_parser;

#endif // COMPUTOR_H
