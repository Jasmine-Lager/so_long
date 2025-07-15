/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:03:24 by jlager            #+#    #+#             */
/*   Updated: 2024/10/05 19:47:15 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// takes two parameters, a string and a function
// applyes the function f to !!every character!! of the string s
// but doesn't return anything and works directly on the original string

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

// looping over the whole original string
// apply the function f to the character at index i
// passing i and the address to s[i] as parameter to f
// f will update the original string directly