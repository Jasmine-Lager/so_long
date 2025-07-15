/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:48:07 by jlager            #+#    #+#             */
/*   Updated: 2025/04/18 16:36:24 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	exit_error(char *message, t_game *game)
{
	ft_putstr_fd("Error\n", 2);
	if (message && message[0] != '\0')
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
	}
	cleanup_and_exit(game);
	exit(EXIT_FAILURE);
}

void	free_map_grid(t_map *map)
{
	int	y;

	if (!map || !map->grid)
		return ;
	y = 0;
	while (map->grid[y] != NULL && y < map->height)
	{
		free(map->grid[y]);
		map->grid[y] = NULL;
		y++;
	}
	free(map->grid);
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
}

void	destroy_images(t_game *game)
{
	if (!game->mlx_ptr)
		return ;
	if (game->img.floor)
		mlx_destroy_image(game->mlx_ptr, game->img.floor);
	if (game->img.wall)
		mlx_destroy_image(game->mlx_ptr, game->img.wall);
	if (game->img.player)
		mlx_destroy_image(game->mlx_ptr, game->img.player);
	if (game->img.collectible)
		mlx_destroy_image(game->mlx_ptr, game->img.collectible);
	if (game->img.exit_closed)
		mlx_destroy_image(game->mlx_ptr, game->img.exit_closed);
	if (game->img.exit_open)
		mlx_destroy_image(game->mlx_ptr, game->img.exit_open);
	ft_memset(&game->img, 0, sizeof(t_img));
}

int	cleanup_and_exit(t_game *game)
{
	if (!game)
		exit(EXIT_SUCCESS);
	free_map_grid(&game->map);
	destroy_images(game);
	if (game->mlx_ptr && game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	ft_printf("Game resources cleaned up. Exiting.\n");
	exit(EXIT_SUCCESS);
	return (0);
}

// mac
// int	cleanup_and_exit(t_game *game)
// {
// 	if (!game)
// 		exit(EXIT_SUCCESS);
// 	free_map_grid(&game->map);
// 	destroy_images(game);
// 	if (game->mlx_ptr && game->win_ptr)
// 	{
// 		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
// 		game->win_ptr = NULL;
// 	}
// #ifndef __APPLE__
// 	if (game->mlx_ptr)
// 	{
// 		mlx_destroy_display(game->mlx_ptr);
// 		free(game->mlx_ptr);
// 		game->mlx_ptr = NULL;
// 	}
// #endif

// 	ft_printf("Game resources cleaned up. Exiting.\n");
// 	exit(EXIT_SUCCESS);
// 	return (0);
// }