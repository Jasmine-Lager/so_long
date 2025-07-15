/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:48:12 by jlager            #+#    #+#             */
/*   Updated: 2025/04/18 16:39:49 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	read_and_process_lines(int fd, t_map *map, int *status,
		char **line_ptr)
{
	int		keep_reading;
	char	*current_line;

	while (*status == 1 && *line_ptr != NULL)
	{
		current_line = *line_ptr;
		process_map_line(current_line, map, status);
		free(current_line);
		*line_ptr = NULL;
		keep_reading = (*status == 1);
		if (keep_reading)
			*line_ptr = get_next_line(fd);
	}
}

int	get_map_dimensions(int fd, t_map *map)
{
	char	*line;
	int		status;

	status = 1;
	map->height = 0;
	map->width = -1;
	line = get_next_line(fd);
	read_and_process_lines(fd, map, &status, &line);
	if (status == 1 && (map->height == 0 || map->width <= 0))
	{
		ft_putstr_fd("Error: Map is empty or has invalid dimensions.\n", 2);
		status = 0;
	}
	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
	return (status);
}

int	process_map_dimensions(const char *filename, t_map *map)
{
	int	fd;
	int	success;

	success = 0;
	map->width = 0;
	map->height = 0;
	map->grid = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening map file");
		return (0);
	}
	if (get_map_dimensions(fd, map))
		success = 1;
	else
		ft_putstr_fd("Error: Failed to read map dimensions.\n", 2);
	if (close(fd) == -1)
		perror("Error closing map file after dimension check");
	return (success);
}

int	populate_map_grid(const char *filename, t_map *map)
{
	int	fd;
	int	success;

	success = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening map file");
		return (0);
	}
	if (fill_map_grid(fd, map))
		success = 1;
	if (close(fd) == -1)
		perror("Error closing map file after grid fill");
	if (!success)
		ft_putstr_fd("Error: Failed to fill map grid.\n", 2);
	return (success);
}

int	read_map(const char *filename, t_game *game)
{
	if (!check_filename(filename))
		return (0);
	if (!process_map_dimensions(filename, &game->map))
		return (0);
	if (!populate_map_grid(filename, &game->map))
		return (0);
	if (game->map.width < 3 || game->map.height < 3)
	{
		free_map_grid(&game->map);
		ft_putstr_fd("Error: Map is too small (minimum 3x3 required).\n", 2);
		return (0);
	}
	return (1);
}
