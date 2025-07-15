/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jasminelager <jasminelager@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:59:33 by jasminelage       #+#    #+#             */
/*   Updated: 2025/04/05 19:08:06 by jasminelage      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	found_newline(t_list *list)
{
	int	i;

	if (NULL == list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buff[i] && i < BUFFER_SIZE)
		{
			if (list->str_buff[i] == '\n')
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}

void	polish_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		j;
	char	*buff;

	buff = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (NULL == buff || NULL == clean_node)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	j = 0;
	while (last_node->str_buff[i] && last_node->str_buff[i] != '\n')
		++i;
	while (last_node->str_buff[i] && last_node->str_buff[i++])
		buff[j++] = last_node->str_buff[i];
	buff[j] = '\0';
	clean_node->str_buff = buff;
	clean_node->next = NULL;
	dealloc(list, clean_node, buff);
}

char	*get_a_line(t_list *list)
{
	int		length;
	char	*next_str;

	if (NULL == list)
		return (NULL);
	length = length_to_newline(list);
	next_str = malloc(length + 1);
	if (NULL == next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void	create_list(t_list **list, int fd)
{
	int		read_char;
	char	*buff;
	t_list	*temporary;

	while (!found_newline(*list))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (NULL == buff)
			return ;
		read_char = read(fd, buff, BUFFER_SIZE);
		if (!read_char || read_char < 0)
		{
			while (*list && read_char < 0)
			{
				temporary = (*list)->next;
				free((*list)->str_buff);
				free(*list);
				*list = temporary;
			}
			free(buff);
			return ;
		}
		buff[read_char] = '\0';
		append(list, buff);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_a_line(list);
	polish_list(&list);
	return (next_line);
}
