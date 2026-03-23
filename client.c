#include "minitalk.h"

#include <stdio.h>

volatile sig_atomic_t g_ack = 0;

void	ack_handler(int signal)
{
	(void)signal;
	g_ack = 1;
}

int main(int ac, char **av)
{
	struct sigaction	action;
	int	pid;
	char	*signal;
	int	i;
	int	j;

	if (ac != 3)
		return (0);
	action.sa_handler = ack_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	pid = atoi(av[1]);
	signal = av[2];
	i = 0;
	sigaction(SIGUSR1, &action, NULL);
	while (signal[i])
	{
		j = 0;
		g_ack = 0;
		while (j < 8)
		{
			if (signal[i] >> j & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
			j++;
		}
		while (g_ack == 0)
			pause();
		usleep(100);
		i++;
	}
	while (j > 0)
	{
		kill(pid, SIGUSR1);
		usleep(100);
		j--;
	}
	while (g_ack == 0)
			pause();
	usleep(100);
	return 0;
}

