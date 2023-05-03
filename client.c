/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 06:02:29 by hel-haia          #+#    #+#             */
/*   Updated: 2023/05/01 18:43:31 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sift_char(char s, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		usleep(800);
		if (s & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		s >>= 1;
		i++;
	}
}

void	brain(int id, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		sift_char(s[i], id);
		i++;
	}
	sift_char(0, id);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		return (1);
	pid = ft_atoi(argv[1]);
	if (pid == -1)
		return (1);
	brain(pid, argv[2]);
	return (0);
}
