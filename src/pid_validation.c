/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pid_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/28 11:39:52 by dloustal      #+#    #+#                 */
/*   Updated: 2025/02/28 13:37:31 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minitalk.h"

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	valid_pid(const char *nptr)
{
	int		nb;
	char	*str;

	str = (char *)nptr;
	nb = 0;
	if (ft_strlen(str) == 1 && *str == '0')
		return (0);
	else if (*str == '0' || *str == 0)
		return (-1);
	while (is_digit(*str))
	{
		nb *= 10;
		nb += *str - '0';
		if (nb > 4194304)
			return (-1);
		str++;
	}
	if (*str)
		return (-1);
	return (nb);
}
