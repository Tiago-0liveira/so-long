/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:18:09 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/10/27 21:42:02 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "bool.h"

# define USAGE "Usage: ./so_long [<map-path>.ber]\n"

# define MAP_FILE_EXTENSION ".ber"

# define WALL_PATH "./assets/wall.xpm"
# define PLAYER_PATH "./assets/player.xpm"
# define GROUND_PATH "./assets/ground.xpm"
# define EXIT_PATH "./assets/key.xpm"
# define ITEM_PATH "./assets/princess.xpm"

# define IMAGE_SIZE 64

# define MSG_INVALID_MAP_DIMENSIONS "Invalid map dimensions!\n"
# define MSG_INVALID_MAP_IDENTIFIER "Invalid map identifier!\n"
# define MSG_INVALID_MAP_PATH "Invalid map path!\n"

typedef struct _t_map
{
	char				**map;
	int					width;
	int					height;
}						t_map;

typedef struct _t_win
{
	void				*mlx;
	void				*win;
}						t_win;

typedef struct _t_xpm_image
{
	int					width;
	int					height;
	void				*p_img;
}						t_xpm_image;

typedef struct _t_assets
{
	t_xpm_image			*wall;
	t_xpm_image			*ground;
	t_xpm_image			*player;
	t_xpm_image			*item;
	t_xpm_image			*exit;
}						t_assets;

typedef struct _t_player
{
	int					x;
	int					y;
	int					items;
	int					moves;
}						t_player;

typedef struct _t_game
{
	t_assets			*assets;
	t_map				*map;
	t_player			*player;
}						t_game;

typedef struct _t_so_long
{
	t_win				*win;
	t_game				*game;
}						t_so_long;

enum					e_hooking_event
{
	KeyPress = 2,
	DestroyNotify = 17,
};

enum					e_event_mask
{
	NoEventMask = 0L,
	KeyPressMask = (1L << 0)
};

enum					e_map_check_error
{
	NO_ERROR = 0,
	MAP_NOT_FOUND = 1,
	INVALID_MAP_EXTENSION = 2,
	INVALID_MAP_DIMENSIONS = 3,
	INVALID_MAP_IDENTIFIER = 4,
	INVALID_PATH = 5,
};

enum					e_key_code
{
	K_W = 119,
	K_A = 97,
	K_S = 115,
	K_D = 100,
	K_UP = 65362,
	K_LEFT = 65361,
	K_DOWN = 65364,
	K_RIGHT = 65363,
	K_ESC = 65307,
};

enum					e_map_identifiers
{
	EMPTY = '0',
	WALL = '1',
	ITEM = 'C',
	EXIT = 'E',
	PLAYER = 'P',
	INVALID = 'X',
};

enum					e_player_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

// main.c
int						main(int argc, char **argv);
t_win					*win_init(int width, int height);

// eventHandlers.c
void					init_event_handlers(t_so_long *so_long);

// map.c
t_bool					check_args(int argc, char *argv[]);
enum e_map_identifiers	get_identifier(char c);
t_bool					is_valid_identifier(char c);
t_xpm_image				*get_img_from_identifier(t_assets *assets,
							enum e_map_identifiers identifier);
enum e_map_check_error	get_map_size(int fd, int *width, int *height);
t_map					*load_map(char *path, int *width, int *height);
t_map					*check_map(char *path);
t_map					*map_init(int width, int height);
void					free_map(t_map *map);
void					update_map(t_so_long *so_long);

// img.c

t_xpm_image				*load_xpm_img(void *mlx, char *path);
t_assets				*load_assets(void *mlx);
void					render_map(t_win *win, t_game *game);
void					free_xpm_img(void *mlx, t_xpm_image *img);
void					free_assets(void *mlx, t_assets *assets);

// utils.c
t_bool					ends_with(char *str, char *end);
void					free_map(t_map *map);
void					free_game(void *mlx, t_game *game);
void					close_win(t_so_long *so_long);
void					free_win(t_win *win);

// player.c

t_player				*player_init(int x, int y);
t_bool					player_can_move(t_game *game,
							enum e_player_direction dir);
void					set_dir_value(enum e_player_direction \
							dir, int *x, int *y);
t_bool					move_player(t_so_long *so_long, enum e_player_direction dir);

#endif
