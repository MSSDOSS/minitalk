/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 01:01:53 by hel-haia          #+#    #+#             */
/*   Updated: 2023/04/29 20:07:11 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	fill_bit(int signal, char c, int i)
{
	if (signal == SIGUSR1)
		c |= 1 << i;
	if (signal == SIGUSR2)
		c &= ~(1 << i);
	return (c);
}

void	lhandler(int sig, siginfo_t *inf)
{
	static int	pids;
	static int	i;
	static char	c;

	if (pids != inf->si_pid)
	{
		pids = inf->si_pid;
		write(1, "\n", 1);
		i = 0;
		c = 0;
	}
	c = fill_bit(sig, c, i);
	i++;
	if (i == 8)
	{
		if (c == 0)
		{
			usleep(500);
			kill(pids, SIGUSR1);
		}
		write(1, &c, 1);
		c = 0;
		i = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	int					id;

	write(1, "My PID is: ", 12);
	id = getpid();
	ft_putnbr_fd(id, 1);
	write(1, "\n", 1);
	sa.sa_handler = (void *)lhandler;
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
}
