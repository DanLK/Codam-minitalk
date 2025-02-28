/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/28 11:52:11 by dloustal      #+#    #+#                 */
/*   Updated: 2025/02/28 16:11:28 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "../libft/libft.h"

typedef struct s_buffer
{
	sig_atomic_t	bit;
	sig_atomic_t	position;
	sig_atomic_t	num;
	char			buffer[131072];
}		t_buffer;

// PID Validation
int	valid_pid(const char *nptr);
