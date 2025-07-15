/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:08:40 by jlager            #+#    #+#             */
/*   Updated: 2024/10/05 18:15:12 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	i = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (size == 0)
		return (src_len);
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

/*
#include <stdio.h>
int main(void)
{
	char *src = "Hello, World!";
	char dst[20]; //20 bit buffer
	int result;
	
	result = ft_strlcpy(dst, src, sizeof(dst));
	
	printf("Source: %s\n", src);
	printf("Destination: %s\n", dst);
	printf("Returned length: %d\n", result);
	printf("Destination buffer size: %lu\n", sizeof(dst));

	return (0);
}
*/

// % - indicates the start of a format specifier in printf
// l (lowercase L) - is a length modifier, indicates a "long" integer
// u - specifies that we're dealing with an unsigned integer

// > %lu together means "print this value as an unsigned long integer".
// 	sizeof returns a value of type size_t.
// 	size_t is typically defined as an unsigned long integer on most systems.

// %zu - specifically designed for size_t values in C99 and later standards
