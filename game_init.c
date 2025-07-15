/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:48:01 by jlager            #+#    #+#             */
/*   Updated: 2025/04/18 16:01:13 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game_struct(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->mlx_ptr = NULL;
	game->win_ptr = NULL;
	game->map.grid = NULL;
}

void	init_mlx_and_window(t_game *game)
{
	int	win_width;
	int	win_height;

	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		exit_error("Fatal: Failed to initialize MiniLibX connection.", game);
	win_width = game->map.width * TILE_SIZE;
	win_height = game->map.height * TILE_SIZE;
	game->win_ptr = mlx_new_window(game->mlx_ptr, win_width, win_height,
			"so_long - The C Game");
	if (!game->win_ptr)
		exit_error("Fatal: Failed to create game window.", game);
}

static void	check_asset_dimensions(t_game *game, int w, int h)
{
	if (w != TILE_SIZE || h != TILE_SIZE)
	{
		ft_putstr_fd("Warning: Asset dimensions do not match TILE_SIZE.\n", 1);
		game->img.width = w;
		game->img.height = h;
	}
}

void	load_assets(t_game *game)
{
	int	w;
	int	h;

	game->img.width = TILE_SIZE;
	game->img.height = TILE_SIZE;
	w = game->img.width;
	h = game->img.height;
	game->img.floor = mlx_xpm_file_to_image(game->mlx_ptr, "assets/floor.xpm",
			&w, &h);
	game->img.wall = mlx_xpm_file_to_image(game->mlx_ptr, "assets/wall.xpm", &w,
			&h);
	game->img.player = mlx_xpm_file_to_image(game->mlx_ptr, "assets/player.xpm",
			&w, &h);
	game->img.collectible = mlx_xpm_file_to_image(game->mlx_ptr,
			"assets/collectible.xpm", &w, &h);
	game->img.exit_closed = mlx_xpm_file_to_image(game->mlx_ptr,
			"assets/exit_closed.xpm", &w, &h);
	game->img.exit_open = mlx_xpm_file_to_image(game->mlx_ptr,
			"assets/exit_open.xpm", &w, &h);
	if (!game->img.floor || !game->img.wall || !game->img.player
		|| !game->img.collectible || !game->img.exit_closed
		|| !game->img.exit_open)
		exit_error("Error - Failed to load XPM files", game);
	check_asset_dimensions(game, w, h);
}
