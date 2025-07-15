/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:07:59 by jlager            #+#    #+#             */
/*   Updated: 2024/10/05 18:41:06 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// It copies the character c into all the allocated memmory, amount of bytes

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temporary;

	temporary = (unsigned char *) b;
	while (len > 0)
	{
		*(temporary++) = (unsigned char) c;
		len--;
	}
	return (b);
}

// The value of c will be converted to an unsigned char, so to set this value in
// the b string, we'll have to convert the b string to pointer to unsigned char
