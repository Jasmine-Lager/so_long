/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:48:05 by jlager            #+#    #+#             */
/*   Updated: 2025/04/18 11:48:35 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tile(t_game *game, void *img_ptr, int x, int y)
{
	if (!game->win_ptr || !img_ptr)
		return ;
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img_ptr, x
		* TILE_SIZE, y * TILE_SIZE);
}

void	render_map_tiles(t_game *game, void *exit_img)
{
	int		x;
	int		y;
	char	tile;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			tile = game->map.grid[y][x];
			draw_tile(game, game->img.floor, x, y);
			if (tile == WALL)
				draw_tile(game, game->img.wall, x, y);
			else if (tile == COLLECTIBLE)
				draw_tile(game, game->img.collectible, x, y);
			else if (tile == EXIT)
				draw_tile(game, exit_img, x, y);
			else if (tile == PLAYER)
				draw_tile(game, game->img.player, x, y);
			x++;
		}
		y++;
	}
}

int	ft_num_digits(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa_moves(int moves)
{
	char	*str;
	int		num_digits;
	int		total_len;

	num_digits = ft_num_digits(moves);
	total_len = 7 + num_digits;
	str = initialize_string(num_digits);
	if (!str)
		return (NULL);
	append_number(str, moves, total_len);
	return (str);
}

int	render_game(t_game *game)
{
	void	*exit_img;
	char	*move_str;

	if (!game->win_ptr)
		return (1);
	if (game->collected == game->map.collectibles)
		exit_img = game->img.exit_open;
	else
		exit_img = game->img.exit_closed;
	render_map_tiles(game, exit_img);
	move_str = ft_itoa_moves(game->moves);
	if (!move_str)
	{
		perror("Failed to create move string");
		return (1);
	}
	if (game->mlx_ptr && game->win_ptr)
		mlx_string_put(game->mlx_ptr, game->win_ptr, 10, 10, 0xFFFFFF,
			move_str);
	free(move_str);
	return (0);
}
