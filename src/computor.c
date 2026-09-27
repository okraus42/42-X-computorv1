#include <stdio.h> //printf, dprintf
#include <string.h> // memset
#include "computor.h" //t_token


// The equation in its reduced form.
// The degree of the equation.
// It’s solution(s) and the polarity of the discriminant if it makes sens.

int parse(t_parser *parser);

void reduce(t_parser *parser);

int computor(char const *equation)
{
	t_parser parser;

	if (equation == NULL)
	{
		dprintf(2, "Usage:\n");
		return (1);
	}
	memset(&parser, 0, sizeof(parser));
	printf("The equation is: %s\n", equation);
	parser.equation = equation;
	// parse and reduce
	if (parse(&parser))
		return (1);
	// print reduced form
	reduce(&parser);
	// solve

	return (0);
}
