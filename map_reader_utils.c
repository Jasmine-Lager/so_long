/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:48:11 by jlager            #+#    #+#             */
/*   Updated: 2025/04/18 13:20:17 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_map_dimensions(int current_len, t_map *map, int *status_ptr)
{
	if (map->width == -1)
		map->width = current_len;
	else if (map->width != current_len)
	{
		ft_putstr_fd("Error: Map is not rectangular.\n", 2);
		*status_ptr = 0;
	}
	if (*status_ptr == 1)
		map->height++;
}

void	process_map_line(char *line, t_map *map, int *status_ptr)
{
	int	current_len;

	current_len = ft_strlen(line);
	if (current_len > 0 && line[current_len - 1] == '\n')
	{
		line[current_len - 1] = '\0';
		current_len--;
	}
	if (current_len == 0)
	{
		if (map->height > 0)
		{
			ft_putstr_fd("Error: Empty line found within map content.\n", 2);
			*status_ptr = 0;
		}
	}
	else
		update_map_dimensions(current_len, map, status_ptr);
}

int	free_grid_on_error(t_map *map, int lines_filled, char *current_line)
{
	if (current_line)
		free(current_line);
	while (--lines_filled >= 0)
	{
		if (map->grid[lines_filled])
			free(map->grid[lines_filled]);
	}
	if (map->grid)
		free(map->grid);
	map->grid = NULL;
	return (0);
}

int	read_and_validate_line(int fd, int expected_width, char **line_ptr)
{
	size_t	len;

	*line_ptr = get_next_line(fd);
	if (!(*line_ptr))
	{
		ft_putstr_fd("Error: Read error.\n", 2);
		return (0);
	}
	len = ft_strlen(*line_ptr);
	if (len > 0 && (*line_ptr)[len - 1] == '\n')
		(*line_ptr)[len - 1] = '\0';
	if (ft_strlen(*line_ptr) != (size_t)expected_width)
	{
		ft_putstr_fd("Error: Map row has inconsistent width.\n", 2);
		free(*line_ptr);
		*line_ptr = NULL;
		return (0);
	}
	return (1);
}

int	fill_map_grid(int fd, t_map *map)
{
	char	*validated_line;
	int		y;

	validated_line = NULL;
	y = 0;
	map->grid = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (ft_putstr_fd("Error: Failed malloc map grid memory.\n", 2), 0);
	while (y < map->height)
	{
		if (!read_and_validate_line(fd, map->width, &validated_line))
			return (free_grid_on_error(map, y, NULL));
		map->grid[y] = ft_strdup(validated_line);
		free(validated_line);
		validated_line = NULL;
		if (!map->grid[y])
		{
			ft_putstr_fd("Error: dupe map line (strdup failed).\n", 2);
			return (free_grid_on_error(map, y, NULL));
		}
		y++;
	}
	map->grid[y] = NULL;
	return (1);
}
