/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:45:40 by jasminelage       #+#    #+#             */
/*   Updated: 2025/04/18 15:22:58 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	char		number;
	int			i;
	long int	long_n;

	long_n = (long int)n;
	i = 0;
	if (long_n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (long_n < 0)
	{
		write(1, "-", 1);
		long_n = -long_n;
		i++;
	}
	if (long_n >= 10)
		i += ft_putnbr(long_n / 10);
	number = (long_n % 10) + '0';
	write(1, &number, 1);
	i++;
	return (i);
}

int	ft_puthex(int n, char format)
{
	char			*symbols;
	int				i;
	unsigned int	save_n;

	i = 0;
	save_n = (unsigned int)n;
	if (format == 'X')
		symbols = "0123456789ABCDEF";
	else
		symbols = "0123456789abcdef";
	if (save_n >= 16)
		i += ft_puthex(save_n / 16, format);
	i += write(1, &symbols[save_n % 16], 1);
	return (i);
}

int	choose_format(const char format, va_list args)
{
	int	printed_chars;

	printed_chars = 0;
	if (format == 'c')
		printed_chars = ft_putchar(va_arg(args, int));
	else if (format == 's')
		printed_chars = ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		printed_chars = ft_putptr(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		printed_chars = ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		printed_chars = ft_putunbr(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		printed_chars = ft_puthex(va_arg(args, int), format);
	else if (format == '%')
		printed_chars = ft_putchar('%');
	return (printed_chars);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed_chars;

	printed_chars = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			printed_chars += choose_format(*format, args);
		}
		else
			printed_chars += ft_putchar(*format);
		format++;
	}
	va_end(args);
	return (printed_chars);
}

// A variadic function is one which accepts a variable number of arguments
// It is characterized by the "..." in a function.
// va_list - new object type
// 		suitable for holding the information needed by the macros
// va_start, va_copy, va_arg, and va_end
// 		> it is a list that will contain all the dynamic arguments.
// 		Declaired: va_list    any_name_you_want;
// va_start - function macro - initilizing
// 		this will somehow initialize everything, ...
// 		... before we start moving through our variable argument list (va_list)
// 		Called: va_start( va_list var, parameterN )
// va_start must be called before any use of va_arg
// 		otherwise your va_list variable/table will be empty
// va_arg - function macro
// 		This macro allows access to the arguments of the variadic function
// 		Each time va_arg is called, you move to the next argument
// 		Called: va_arg( va_list var, type_of_the_variable )
// va_end - function macro - don't forget to clean up the object
// 		frees allocated memmory
// 		Called: va_end( va_list var );