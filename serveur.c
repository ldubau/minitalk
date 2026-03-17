#include "minitalk.h"

#include <stdio.h>

void	handler(int	signal)
{
	static int	pos;
	static char	c;

	if (signal == SIGUSR2)
		c |= 1 << pos;
	pos++;
	if (pos == 8)
	{
		write(1, &c, 1);
		pos = 0;
		c = 0;
	}
}

int main()
{
	struct sigaction	action;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	printf("PID : %d\n", getpid());
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
	return 0;
}
