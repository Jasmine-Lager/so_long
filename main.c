/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:48:09 by jlager            #+#    #+#             */
/*   Updated: 2025/04/18 16:38:12 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_filename(const char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ".ber", 5) != 0)
	{
		ft_putstr_fd("Error: Map file must have a '.ber' extension.\n", 2);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_game_struct(&game);
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" <map_file.ber>\n", 2);
		return (EXIT_FAILURE);
	}
	if (!read_map(argv[1], &game))
		return (cleanup_and_exit(&game), EXIT_FAILURE);
	if (!validate_map(&game))
		return (cleanup_and_exit(&game), EXIT_FAILURE);
	ft_printf("Collect %d batteries to exit!\n", game.map.collectibles);
	init_mlx_and_window(&game);
	load_assets(&game);
	mlx_key_hook(game.win_ptr, handle_keypress, &game);
	mlx_hook(game.win_ptr, EVENT_CLOSE_BTN, (1L << 17), handle_close_event,
		&game);
	mlx_expose_hook(game.win_ptr, render_game, &game);
	render_game(&game);
	mlx_loop(game.mlx_ptr);
	cleanup_and_exit(&game);
	return (EXIT_SUCCESS);
}
