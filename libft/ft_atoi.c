/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:45:53 by jlager            #+#    #+#             */
/*   Updated: 2024/10/05 18:48:14 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// converts a string into its integer value (const char *str)
// it handles whitespace, a sign (+ or -) and the numeric characters

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				rslt;
	int				sgn;

	i = 0;
	rslt = 0;
	sgn = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
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
