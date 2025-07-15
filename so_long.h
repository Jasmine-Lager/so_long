/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlager <jlager@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:48:17 by jlager            #+#    #+#             */
/*   Updated: 2025/04/18 16:39:49 by jlager           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WALL '1'
# define FLOOR '0'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

# define TILE_SIZE 32

// macOS values:
# ifdef __APPLE__
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ESC 53
#  define EVENT_CLOSE_BTN 17
// Linux values:
# else
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_ESC 65307
#  define EVENT_CLOSE_BTN 17
# endif

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		player_count;
	int		exit_count;
}			t_map;

typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectible;
	void	*exit_closed;
	void	*exit_open;
	int		width;
	int		height;
}			t_img;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	map;
	t_img	img;
	int		moves;
	int		collected;
	int		exit_reachable;
	int		collectibles_reachable;
}			t_game;

// game_hooks.c
int			handle_keypress(int keycode, t_game *game);
int			handle_close_event(t_game *game);

// game_init.c
void		init_game_struct(t_game *game);
void		init_mlx_and_window(t_game *game);
void		load_assets(t_game *game);

// game_render_utils.c
char		*initialize_string(int num_digits);
void		append_number(char *str, int moves, int total_len);

// game_render.c
void		draw_tile(t_game *game, void *img_ptr, int x, int y);
void		render_map_tiles(t_game *game, void *exit_img);
int			ft_num_digits(int n);
char		*ft_itoa_moves(int moves);
int			render_game(t_game *game);

// game_utils.c
void		ft_putstr_fd(char *s, int fd);
void		exit_error(char *message, t_game *game);
void		free_map_grid(t_map *map);
void		destroy_images(t_game *game);
int			cleanup_and_exit(t_game *game);

// map_reader_utils.c
void		update_map_dimensions(int current_len, t_map *map, int *status_ptr);
void		process_map_line(char *line, t_map *map, int *status_ptr);
int			free_grid_on_error(t_map *map, int lines_filled,
				char *current_line);
int			read_and_validate_line(int fd, int expected_width, char **line_ptr);
int			fill_map_grid(int fd, t_map *map);

// main.c - I just dumped this here, it as in map_reader.c
int			check_filename(const char *filename);

// map_reader.c
int			get_map_dimensions(int fd, t_map *map);
int			process_map_dimensions(const char *filename, t_map *map);
int			populate_map_grid(const char *filename, t_map *map);
int			read_map(const char *filename, t_game *game);

// map_validation_utils.c
int			process_char(t_game *game, int x, int y);
int			iterate_and_process_map(t_game *game);
int			validate_map_counts(t_game *game);
char		**create_visited_map(t_map *map);
void		free_visited_map(char **visited, int height);

// map_validation.c
int			validate_map(t_game *game);
int			check_path_validity(t_game *game);
int			check_wall_enclosure(t_map *map);
int			check_map_chars(t_game *game);
void		flood_fill(t_game *game, int x, int y, char **visited_map);

#endif
