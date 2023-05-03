/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   men_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 00:49:59 by hel-haia          #+#    #+#             */
/*   Updated: 2023/04/29 15:14:01 by hel-haia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	isoverflow(long long int prev, long long int curr)
{
	if (curr / 10 == prev)
		return (0);
	return (1);
}

static int	itisspace(const char *str, int *pi)
{
	int	count;
	int	i;

	i = 0;
	count = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45)
	{
		count = -1;
		i++;
	}
	else if (str[i] == 43)
		i++;
	*pi = i;
	return (count);
}

int	ft_atoi(const char *str)
{
	int				sign;
	long long int	res;
	long long int	prv;
	int				i;

	res = 0;
	sign = itisspace(str, &i);
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		prv = res;
		res = res * 10 + (str[i] - 48);
		if (isoverflow(prv, res) == 1)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		i++;
	}
	res *= sign;
	return (res);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int long	nbr;

	nbr = (int long) n;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr *= -1;
	}
	if (n / 10)
		ft_putnbr_fd(nbr / 10, fd);
	ft_putchar_fd(nbr % 10 + '0', fd);
}
