/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:25:30 by jlager            #+#    #+#             */
/*   Updated: 2024/10/05 18:53:32 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

// converts an integer into its string representation (int n)
// it handles negative numbers and allocates memory for the resulting string

static int	get_num_length(int n)
{
	int	length;

	if (n <= 0)
		length = 1;
	else
		length = 0;
	while (n != 0)
	{
		length++;
		n /= 10;
	}
	return (length);
}

static void	reverse_str(char *str, int length)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = length - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

static void	convert_to_str(char *str, int n, int is_negative)
{
	int	i;

	i = 0;
	if (is_negative)
		n = -n;
	while (n != 0)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (is_negative)
		str[i++] = '-';
	str[i] = '\0';
	reverse_str(str, i);
}

char	*ft_itoa(int n)
{
	int		is_negative;
	int		length;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	is_negative = (n < 0);
	length = get_num_length(n);
	str = (char *)malloc(length + 1);
	if (!str)
		return (NULL);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
	}
	else
		convert_to_str(str, n, is_negative);
	return (str);
}
// Helper function to calculate the length of the number
// Helper function to reverse a string
// Helper function to handle the special case for INT_MIN
// Helper function to convert integer to string
