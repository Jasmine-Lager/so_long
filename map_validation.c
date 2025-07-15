/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:48:16 by jlager            #+#    #+#             */
/*   Updated: 2025/04/18 15:27:07 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Base cases for recursion termination:
// 1. Out of bounds
// 2. Hit a wall
// 3. Already visited this tile
// flood_fill(game, x, y - 1, visited_map); // Up
// flood_fill(game, x, y + 1, visited_map); // Down
// flood_fill(game, x - 1, y, visited_map); // Left
// flood_fill(game, x + 1, y, visited_map); // Right

void	flood_fill(t_game *game, int x, int y, char **visited_map)
{
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return ;
	if (game->map.grid[y][x] == WALL)
		return ;
	if (visited_map[y][x] == 'V')
		return ;
	visited_map[y][x] = 'V';
	if (game->map.grid[y][x] == COLLECTIBLE)
		game->collectibles_reachable++;
	if (game->map.grid[y][x] == EXIT)
		game->exit_reachable = 1;
	flood_fill(game, x, y - 1, visited_map);
	flood_fill(game, x, y + 1, visited_map);
	flood_fill(game, x - 1, y, visited_map);
	flood_fill(game, x + 1, y, visited_map);
}

// Main function to check map characters, orchestrating the helpers.
int	check_map_chars(t_game *game)
{
	game->map.collectibles = 0;
	game->map.player_count = 0;
	game->map.exit_count = 0;
	if (!iterate_and_process_map(game))
		return (0);
	if (!validate_map_counts(game))
		return (0);
	return (1);
}

int	check_wall_enclosure(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		if (map->grid[y][0] != WALL || map->grid[y][map->width - 1] != WALL)
			return (ft_putstr_fd("Error: Map must have by walls.\n", 2), 0);
		y += (map->height - 1);
		if (y == 0)
			y = map->height - 1;
		else
			break ;
	}
	x = 0;
	while (x < map->width)
	{
		if (map->grid[0][x] != WALL || map->grid[map->height - 1][x] != WALL)
			return (ft_putstr_fd("Error: Map must have walls.\n", 2), 0);
		x++;
	}
	return (1);
}

int	check_path_validity(t_game *game)
{
	char	**visited_map;
	int		is_valid;

	visited_map = create_visited_map(&game->map);
	if (!visited_map)
	{
		ft_putstr_fd("Error: Memory allocation failed for path check.\n", 2);
		return (0);
	}
	game->exit_reachable = 0;
	game->collectibles_reachable = 0;
	flood_fill(game, game->map.player_x, game->map.player_y, visited_map);
	free_visited_map(visited_map, game->map.height);
	is_valid = 1;
	if (game->collectibles_reachable != game->map.collectibles)
	{
		ft_putstr_fd("Error: Collectibles not reachable by player.\n", 2);
		is_valid = 0;
	}
	if (!game->exit_reachable)
	{
		ft_putstr_fd("Error: Exit not reachable by player.\n", 2);
		is_valid = 0;
	}
	return (is_valid);
}

int	validate_map(t_game *game)
{
	if (!check_map_chars(game))
		return (0);
	if (!check_wall_enclosure(&game->map))
		return (0);
	if (!check_path_validity(game))
		return (0);
	return (1);
}
