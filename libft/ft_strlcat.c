/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:10:23 by jlager            #+#    #+#             */
/*   Updated: 2024/10/06 14:10:46 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	src_len;
	size_t	dest_len;

	src_len = ft_strlen(src);
	if (!dest && !destsize)
		return (src_len);
	dest_len = ft_strlen(dest);
	if (dest_len >= destsize)
		dest_len = destsize;
	if (dest_len == destsize)
		return (destsize + src_len);
	if (src_len < destsize - dest_len)
		ft_memcpy(dest + dest_len, src, src_len + 1);
	else
	{
		ft_memcpy(dest + dest_len, src, destsize - dest_len - 1);
		dest[destsize - 1] = '\0';
	}
	return (dest_len + src_len);
}
