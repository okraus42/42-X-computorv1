/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:05:21 by okraus            #+#    #+#             */
/*   Updated: 2026/10/02 17:02:35 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "computor.h"

// The equation in its reduced form.
// The degree of the equation.
// It’s solution(s) and the polarity of the discriminant if it makes sens.

char	*getline(void)
{
	static char	str[BUFFER_SIZE];
	int			r;

	r = read(0, str, BUFFER_SIZE);
	if (r == BUFFER_SIZE || r <= 0)
		return (NULL);
	if (str[r - 1] == '\n')
		--r;
	str[r] = 0;
	return (str);
}

int	computor(char const *str); //computor.c

int	main(int argc, char *argv[])
{
	char	*str;

	str = NULL;
	if (argc == 1)
		str = getline();
	if (argc == 2)
		str = argv[1];
	return (computor(str));
}
