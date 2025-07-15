/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:48:14 by jlager            #+#    #+#             */
/*   Updated: 2025/04/18 13:23:35 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	process_char(t_game *game, int x, int y)
{
	char	c;

	c = game->map.grid[y][x];
	if (c == PLAYER)
	{
		game->map.player_count++;
		game->map.player_x = x;
		game->map.player_y = y;
	}
	else if (c == EXIT)
	{
		game->map.exit_count++;
		game->map.exit_x = x;
		game->map.exit_y = y;
	}
	else if (c == COLLECTIBLE)
		game->map.collectibles++;
	else if (c != WALL && c != FLOOR)
	{
		ft_putstr_fd("Error: Invalid character '", 2);
		write(2, &c, 1);
		ft_putstr_fd("' found in map.\n", 2);
		return (0);
	}
	return (1);
}

// Helper function to iterate through the map grid and process each character
// Returns 0 if an invalid character is found during iteration, 1 otherwise.
int	iterate_and_process_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (!process_char(game, x, y))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

// Helper function to validate the final counts of Player, Exit,
// and Collectibles
// Returns 0 if any count is invalid, 1 otherwise.

int	validate_map_counts(t_game *game)
{
	if (game->map.player_count != 1)
	{
		ft_putstr_fd("Error: Map must contain exactly one Player 'P'.\n", 2);
		return (0);
	}
	if (game->map.exit_count != 1)
	{
		ft_putstr_fd("Error: Map must contain exactly one Exit 'E'.\n", 2);
		return (0);
	}
	if (game->map.collectibles < 1)
	{
		ft_putstr_fd("Error: Map has to have min one Collectible 'C'.\n", 2);
		return (0);
	}
	return (1);
}

char	**create_visited_map(t_map *map)
{
	char	**visited;
	int		y;

	visited = (char **)malloc(sizeof(char *) * map->height);
	if (!visited)
		return (NULL);
	y = 0;
	while (y < map->height)
	{
		visited[y] = (char *)malloc(sizeof(char) * map->width);
		if (!visited[y])
		{
			while (--y >= 0)
				free(visited[y]);
			free(visited);
			return (NULL);
		}
		ft_memset(visited[y], '0', map->width);
		y++;
	}
	return (visited);
}

void	free_visited_map(char **visited, int height)
{
	int	y;

	if (!visited)
		return ;
	y = 0;
	while (y < height)
	{
		free(visited[y]);
		y++;
	}
	free(visited);
}
