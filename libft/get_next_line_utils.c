/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasminelager <jasminelager@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:59:36 by jasminelage       #+#    #+#             */
/*   Updated: 2025/04/05 19:08:15 by jasminelage      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// delete me test
void	dealloc(t_list **list, t_list *clean_node, char *buff)
{
	t_list	*temporary;

	if (NULL == *list)
		return ;
	while (*list)
	{
		temporary = (*list)->next;
		free((*list)->str_buff);
		free(*list);
		*list = temporary;
	}
	*list = NULL;
	if (clean_node->str_buff[0])
		*list = clean_node;
	else
	{
		free(buff);
		free(clean_node);
	}
}

t_list	*find_last_node(t_list *list)
{
	if (NULL == list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	copy_str(t_list *list, char *str)
{
	int	i;
	int	j;

	if (NULL == list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->str_buff[i])
		{
			if (list->str_buff[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = list->str_buff[i++];
		}
		list = list->next;
	}
	str[j] = '\0';
}

int	length_to_newline(t_list *list)
{
	int	i;
	int	length;

	if (NULL == list)
		return (0);
	length = 0;
	while (list)
	{
		i = 0;
		while (list->str_buff[i])
		{
			if (list->str_buff[i] == '\n')
			{
				++length;
				return (length);
			}
			++i;
			++length;
		}
		list = list->next;
	}
	return (length);
}

void	append(t_list **list, char *buff)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (NULL == new_node)
		return ;
	if (NULL == last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buff = buff;
	new_node->next = NULL;
}
