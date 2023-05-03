/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 02:58:27 by hel-haia          #+#    #+#             */
/*   Updated: 2023/05/01 18:30:47 by hel-haia         ###   ########.fr       */
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

int	byt_checker(unsigned char c)
{
	if ((c >> 4) == 0b1000)
		return (1);
	else if ((c >> 4) == 0b1100)
		return (2);
	else if ((c >> 4) == 0b1110)
		return (3);
	else if ((c >> 4) == 0b1111)
		return (4);
	return (0);
}

void	unicodes(int id, unsigned char c)
{
	static unsigned int	uni_holder;
	static int			i;
	static int			pids;
	int					uni_bytes;

	uni_bytes = 0;
	if (pids != id)
	{
		pids = id;
		write(1, "\n", 1);
		uni_bytes = 0;
		uni_holder = 0;
		i = 0;
	}
	if (uni_bytes == 0)
		uni_bytes = byt_checker(c);
	uni_holder |= (c << i++ *8);
	if (uni_bytes == i)
	{
		write(1, &uni_holder, uni_bytes);
		uni_bytes = 0;
		uni_holder = 0;
		i = 0;
	}	
}

void	lhandler(int sig, siginfo_t *inf)
{
	static int	pids;
	static int	i;
	static char	c;

	if (pids != inf->si_pid)
	{
		pids = inf->si_pid;
		i = 0;
		c = 0;
	}
	c = fill_bit(sig, c, i);
	i++;
	if (i == 8)
	{
		if (c & (1 << 7))
			unicodes(inf->si_pid, c);
		else if (c == 0)
		{
			usleep(800);
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
