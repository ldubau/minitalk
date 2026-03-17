#include "minitalk.h"

#include <stdio.h>

int main(int ac, char **av)
{
	int	pid;
	char	*signal;
	int	i;
	int	j;

	if (ac < 2)
		return (0);
	pid = atoi(av[1]);
	signal = av[2];
	i = 0;
	while (signal[i])
	{
		j = 0;
		while (j < 8)
		{
			if ((signal[i] >> j & 1) == 0)
				kill(pid, SIGUSR1);
			else if ((signal[i] >> j & 1) == 1)
				kill(pid, SIGUSR2);
			j++;
			usleep(100);
		}
		i++;
	}
	return 0;
}

