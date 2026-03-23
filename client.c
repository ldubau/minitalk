/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leondubau <leondubau@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:39:52 by leondubau         #+#    #+#             */
/*   Updated: 2026/03/23 18:09:53 by leondubau        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack = 0;

void	ack_handler(int signal)
{
	(void)signal;
	g_ack = 1;
}

void	minitalk(int i, int j, int pid, char *signal)
{
	int	last_char;

	last_char = 1;
	while (last_char)
	{
		if (signal[i] == 0)
			last_char = 0;
		j = 0;
		g_ack = 0;
		while (j < 8)
		{
			if (signal[i] >> j & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(200);
			while (g_ack == 0)
				pause();
			usleep(200);
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	action;
	char				*signal;
	int					pid;
	int					i;
	int					j;

	if (ac != 3)
		return (0);
	action.sa_handler = ack_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	pid = atoi(av[1]);
	signal = av[2];
	i = 0;
	j = 0;
	sigaction(SIGUSR1, &action, NULL);
	minitalk(i, j, pid, signal);
	return (0);
}
