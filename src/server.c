/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/24 14:29:27 by dloustal      #+#    #+#                 */
/*   Updated: 2025/02/28 15:53:36 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile t_buffer	g_buffer;

void	signal_action(int signum, siginfo_t *info, void *context)
{
	char	c;

	(void)context;
	if (signum == SIGUSR1)
		g_buffer.num = (g_buffer.num << 1) | 1;
	if (signum == SIGUSR2)
		g_buffer.num = (g_buffer.num << 1);
	g_buffer.bit++;
	if (g_buffer.bit == 8)
	{
		c = (char)g_buffer.num;
		g_buffer.buffer[g_buffer.position] = c;
		if (c == '\0')
		{
			write(STDOUT_FILENO, (void *)g_buffer.buffer,
				g_buffer.position + 1);
			write(STDOUT_FILENO, "\n", 1);
			ft_memset((void *)g_buffer.buffer, 0, g_buffer.position + 1);
			g_buffer.position = 0;
		}
		g_buffer.num = 0;
		g_buffer.bit = 0;
		g_buffer.position++;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sigact;

	ft_printf("PID:%d\n", (int)getpid());
	g_buffer.position = 0;
	sigact.sa_sigaction = &signal_action;
	sigact.sa_flags = SA_SIGINFO;
	sigemptyset(&sigact.sa_mask);
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
	{
		ft_putendl_fd("Signal handler on SIGUSR1 failed", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sigact, NULL) == -1)
	{
		ft_putendl_fd("Signal handler on SIGUSR2 failed", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		pause();
	}
	return (0);
}
