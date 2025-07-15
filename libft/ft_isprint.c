/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:02:00 by jlager            #+#    #+#             */
/*   Updated: 2024/10/05 18:47:15 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// checks if the character c is a printable character

int	ft_isprint(int c)
{
	if (!((c >= 32) && (c <= 126)))
		return (0);
	else
		return (1);
}
