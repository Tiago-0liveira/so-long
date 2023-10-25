/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:18:09 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/10/20 02:03:11 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "bool.h"

typedef struct _t_win {
	void	*mlx;
	void	*win;
}	t_win;

typedef struct _t_xpm_image {
	int		width;
	int		height;
	void	*p_img;
}	t_xpm_image;

typedef struct _t_assets {
	t_xpm_image	*leaves;
	t_xpm_image	*walkstone;
	t_xpm_image	*knight;
}	t_assets;

typedef struct _t_game {
	t_assets	*assets;
}	t_game;

enum e_hooking_event {
	KeyPress = 2,
	DestroyNotify = 17,
};

enum e_event_mask {
	NoEventMask = 0L,
	KeyPressMask = (1L<<0)
};

enum e_key_code {
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	UP = 65362,
	LEFT = 65361,
	DOWN = 65364,
	RIGHT = 65363,
	ESC = 65307,
};

// eventHandlers.c
void		init_event_handlers(t_win *win);

// map.c
t_bool		check_args(int argc, char *argv[]);

// img.c

# define LEAVES_PATH "./assets/leaves.xpm"
# define KNIGHT_PATH "./assets/knight.xpm"
# define WALKSTONE_PATH "./assets/walkstone.xpm"

t_xpm_image	*load_xpm_img(void *mlx, char *path);
t_assets	*load_assets(void *mlx);
void		render_assets(t_win *win, t_assets *assets);
void		free_xpm_img(void *mlx, t_xpm_image **img);
void		free_assets(void *mlx, t_assets	**assets);

#endif