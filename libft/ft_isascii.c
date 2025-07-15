/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:59:59 by jlager            #+#    #+#             */
/*   Updated: 2024/10/05 18:46:50 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// checks if the character c is in the ascii table

int	ft_isascii(int c)
{
	if (!((c >= 0) && (c <= 127)))
		return (0);
	else
		return (1);
}
