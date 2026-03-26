/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leondubau <leondubau@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:39:45 by leondubau         #+#    #+#             */
/*   Updated: 2026/03/26 11:55:55 by leondubau        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*g_string;

char	*ft_realloc(char *g_string, char c)
{
	char	*new_string;
	int		i;

	i = 0;
	if (!g_string)
	{
		g_string = malloc(sizeof(char));
		g_string[0] = '\0';
	}
	while (g_string[i])
		i++;
	new_string = malloc(sizeof(char) * ft_strlen(g_string) + 2);
	ft_strlcpy(new_string, g_string, ft_strlen(g_string) + 1);
	free(g_string);
	new_string[i] = c;
	new_string[i + 1] = '\0';
	return (new_string);
}

int	end_string()
{
	ft_printf("%s\n", g_string);
	free(g_string);
	g_string = NULL;
	return (0);
}

void	handler(int signal, siginfo_t *info, void *context)
{
	static int	pos;
	static char	c;
	static int	current_pid;

	(void) context;
	if (current_pid == 0)
		current_pid = info->si_pid;
	if (info->si_pid != current_pid)
	{
		pos = 0;
		c = 0;
		current_pid = info->si_pid;
	}
	if (signal == SIGUSR2)
		c |= 1 << pos;
	pos++;
	if (pos == 8 && c)
	{
		g_string = ft_realloc(g_string, c);
		pos = 0;
		c = 0;
	}
	else if (pos == 8 && !c)
		end_string();
	kill(info->si_pid, SIGUSR1);
}

int	main(int ac, char **av)
{
	struct sigaction	action;

	if (ac != 1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	(void)av;
	action.sa_sigaction = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	ft_printf("PID : %d\n", getpid());
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
	return (0);
}


// if (pos == 8)
// 	{
// 		if (!c)
// 			end_string();
// 		else
// 			g_string = ft_realloc(g_string, c);
// 		pos = 0;
// 		c = 0;
// 	}
