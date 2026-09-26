#include <stdio.h> //printf, dprintf
#include "computor.h" //t_token


// The equation in its reduced form.
// The degree of the equation.
// It’s solution(s) and the polarity of the discriminant if it makes sens.

int parse(t_parser *parser);

int computor(char const *equation)
{
	t_parser parser;

	if (equation == NULL)
	{
		dprintf(2, "Usage:\n");
		return (1);
	}
	printf("The equation is: %s\n", equation);
	// parse
	if (parse(&parser))
		return (1);
	// reduce

	// solve

	return (0);
}
