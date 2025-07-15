/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:55:47 by jlager            #+#    #+#             */
/*   Updated: 2024/10/05 19:39:52 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

// writes a number to a file descriptor

void	ft_putnbr_fd(int nb, int fd)
{
	char	digit;

	if (nb == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (nb < 0 && nb > -2147483648)
	{
		write (fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10 && nb <= 2147483647)
	{
		ft_putnbr_fd(nb / 10, fd);
	}
	digit = '0' + (nb % 10);
	write(fd, &digit, 1);
}

/*
int	ft_atoi(char *str)
{
	unsigned int	i;
	int				rslt;
	int				sgn;

	i = 0;
	rslt = 0;
	sgn = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sgn *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rslt = (rslt * 10) + str[i] - '0';
		i++;
	}
	return (rslt * sgn);
}

int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_putnbr (ft_atoi(argv[1]));
	}
	else
	{
		write (1, "error\n", 6);
	}
	return(0);
}
*/
