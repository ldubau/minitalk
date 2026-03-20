#include "minitalk.h"

#include <stdio.h>

char *global;

void	handler(int signal, siginfo_t *info, void *context)
{
	static int	pos;
	static char	c;

	(void) context;
	if (signal == SIGUSR2)
		c |= 1 << pos;
	pos++;
	if (pos == 8)
	{
		if (!c)
			write(1, "\n", 1);
		write(1, &c, 1);
		pos = 0;
		c = 0;
		kill(info->si_pid, SIGUSR1);
	}
}

int main(int ac, char **av)
{
	struct sigaction	action;

	if (ac != 1)
		printf("Error\n");
	(void)av;
	action.sa_sigaction = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	printf("PID : %d\n", getpid());
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
	return 0;
}
