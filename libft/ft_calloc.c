/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:44:37 by jlager            #+#    #+#             */
/*   Updated: 2024/10/06 14:19:29 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// is similar to malloc but, it rewrites the allocated memory to zero

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*temporary;
	size_t			i;

	i = 0;
	if (count == 0 || size == 0)
		return (malloc(0));
	if ((count * size) < count || (count * size) < size)
		return (NULL);
	temporary = malloc(count * size);
	if (!temporary)
		return (NULL);
	while (i < count * size)
		temporary[i++] = 0;
	return (temporary);
}

// #include <stdio.h>

// int		main(void)
// {
// 	size_t	count = -5;
// 	size_t	size = -5;
// 	size_t	res =   count * size;
// 	printf("count %zu | size %zu | res %zu\n", count, size, res);
// 	printf("oricalloc: %p\n", calloc(count, size));
// 	printf("ft_calloc: %p\n", ft_calloc(count, size));
// 	return (0);
// }
