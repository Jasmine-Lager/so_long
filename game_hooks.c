/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:47:55 by jlager            #+#    #+#             */
/*   Updated: 2025/04/18 12:16:13 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	handle_exit_move(t_game *game)
{
	if (game->collected == game->map.collectibles)
	{
		ft_printf("Congratulations! You escaped in %d moves!\n", game->moves);
		cleanup_and_exit(game);
		return (1);
	}
	else
	{
		ft_printf("Exit is blocked! Collect all items first...\n");
		ft_printf("Need %d more\n", game->map.collectibles - game->collected);
		return (0);
	}
}

static void	handle_collectible_move(t_game *game, int next_x, int next_y)
{
	game->collected++;
	game->map.grid[next_y][next_x] = FLOOR;
	ft_printf("Collected items: %d\n", game->collected);
	if (game->collected == game->map.collectibles)
		ft_printf("You can now exit!\n");
	else
		ft_printf("Need %d more...\n", game->map.collectibles
			- game->collected);
}

static void	attempt_player_move(t_game *game, int next_x, int next_y)
{
	char	target_tile;

	if (next_x < 0 || next_x >= game->map.width || next_y < 0
		|| next_y >= game->map.height)
		return ;
	target_tile = game->map.grid[next_y][next_x];
	if (target_tile == WALL)
		return ;
	if (target_tile == EXIT)
	{
		if (!handle_exit_move(game))
			return ;
	}
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	if (target_tile == COLLECTIBLE)
		handle_collectible_move(game, next_x, next_y);
	game->map.grid[game->map.player_y][game->map.player_x] = FLOOR;
	game->map.grid[next_y][next_x] = PLAYER;
	game->map.player_x = next_x;
	game->map.player_y = next_y;
	render_game(game);
}

int	handle_keypress(int keycode, t_game *game)
{
	int	current_x;
	int	current_y;

	current_x = game->map.player_x;
	current_y = game->map.player_y;
	if (keycode == KEY_ESC)
	{
		ft_printf("ESC key pressed. Exiting game.\n");
		cleanup_and_exit(game);
	}
	else if (keycode == KEY_W)
		attempt_player_move(game, current_x, current_y - 1);
	else if (keycode == KEY_A)
		attempt_player_move(game, current_x - 1, current_y);
	else if (keycode == KEY_S)
		attempt_player_move(game, current_x, current_y + 1);
	else if (keycode == KEY_D)
		attempt_player_move(game, current_x + 1, current_y);
	return (0);
}

int	handle_close_event(t_game *game)
{
	ft_printf("Window close event received. Exiting game.\n");
	cleanup_and_exit(game);
	return (0);
}
