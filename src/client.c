/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/24 14:29:20 by dloustal      #+#    #+#                 */
/*   Updated: 2025/02/28 15:50:38 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_received = 0;

void	sig_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		g_received = 1;
	}
	else
		(void)signum;
}

void	send_char(char c, int pid)
{
	int	bit;
	int	timeout;

	bit = 7;
	timeout = 0;
	while (bit >= 0)
	{
		g_received = 0;
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_received)
		{
			usleep(100);
			timeout += 100;
			if (timeout >= 5000000)
			{
				ft_putendl_fd("Timeout: no response from server",
					STDERR_FILENO);
				exit(EXIT_FAILURE);
			}
		}
		bit--;
	}
}

void	send_string(char *str, int pid)
{
	struct sigaction	sigact;

	if (!str)
		return ;
	sigact.sa_handler = &sig_handler;
	sigact.sa_flags = 0;
	sigemptyset(&sigact.sa_mask);
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
	{
		ft_putendl_fd("Signal handling failed", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		send_char(*str, pid);
		if (*str == '\0')
			break ;
		str++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (argc != 3)
	{
		ft_putendl_fd("Usage: <Server PID> <Message>", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	pid = valid_pid(argv[1]);
	if (pid == -1)
	{
		ft_putendl_fd("Invalid Server PID format", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (kill(pid, 0) == -1)
	{
		ft_putendl_fd("Inexistent server PID", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	str = argv[2];
	send_string(str, pid);
	return (EXIT_SUCCESS);
}
