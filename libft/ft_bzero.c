/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:42:01 by jlager            #+#    #+#             */
/*   Updated: 2024/10/05 18:48:03 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// it copies 0 into all the allocated memmory, amount of bytes
// same as memset, just always writes 0

void	ft_bzero(void *s, size_t n)
{
	char	*temporary;
	size_t	i;

	i = 0;
	temporary = (char *) s;
	while (n > 0)
	{
		temporary[i] = 0;
		n--;
		i++;
	}
}
