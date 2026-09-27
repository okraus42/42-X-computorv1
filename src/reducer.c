#include "computor.h"
#include <stdio.h>

void reduce(t_parser *parser)
{
	int i = 0;
	int sign = 1;

	printf("Reduced form: ");
	while (i <= parser->max_power)
	{
		printf("%g * X^%i", parser->left[i].value * sign, i);
		i++;
		if (i <= parser->max_power)
		{
			if (parser->left[i].value < 0)
			{
				sign = -1;
				printf(" - ");
			}
			else
			{
				sign = 1;
				printf(" + ");
			}
		}
	}
	printf(" = 0\n");
}