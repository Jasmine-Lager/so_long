/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:28:51 by jasminelage       #+#    #+#             */
/*   Updated: 2025/04/18 15:23:02 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr(unsigned int n)
{
	int	i;

	i = 0;
	if (n >= 10)
		i += ft_putunbr(n / 10);
	i += ft_putchar((n % 10) + '0');
	return (i);
}

int	ft_putptrhex(unsigned long n)
{
	char	*base;
	int		i;

	base = "0123456789abcdef";
	i = 0;
	if (n >= 16)
		i += ft_putptrhex(n / 16);
	i += ft_putchar(base[n % 16]);
	return (i);
}

int	ft_putptr(void *ptr)
{
	unsigned long	address;
	int				i;

	if (!ptr)
		return (ft_putstr("(nil)"));
	address = (unsigned long)ptr;
	i = 0;
	i += ft_putstr("0x");
	i += ft_putptrhex(address);
	return (i);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}
