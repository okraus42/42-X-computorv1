#include <unistd.h>
#include "computor.h"


// The equation in its reduced form.
// The degree of the equation.
// It’s solution(s) and the polarity of the discriminant if it makes sens.

char *getline(void)
{
	static char equation[BUFFER_SIZE];
	int r = 0;

	r = read(0, equation, BUFFER_SIZE);
	if (r == BUFFER_SIZE || r <= 0)
		return NULL;
	if (equation[r - 1] == '\n')
		--r;
	equation[r] = 0;
	return equation;
}

int computor(char const *equation); //computor.c

int main(int argc, char *argv[])
{

	char *equation = NULL;
	if (argc == 1)
		equation = getline();
	if (argc == 2)
		equation = argv[1];
	return (computor(equation));
}
