/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:48:03 by jlager            #+#    #+#             */
/*   Updated: 2025/04/18 11:48:36 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	append_number(char *str, int moves, int total_len)
{
	int	i;
	int	temp_moves;

	if (moves == 0)
		str[7] = '0';
	else
	{
		i = total_len - 1;
		temp_moves = moves;
		while (temp_moves > 0)
		{
			str[i] = (temp_moves % 10) + '0';
			temp_moves /= 10;
			i--;
		}
	}
}

char	*initialize_string(int num_digits)
{
	char	*str;
	int		total_len;

	total_len = 7 + num_digits;
	str = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!str)
		return (NULL);
	str[0] = 'M';
	str[1] = 'o';
	str[2] = 'v';
	str[3] = 'e';
	str[4] = 's';
	str[5] = ':';
	str[6] = ' ';
	str[total_len] = '\0';
	return (str);
}
