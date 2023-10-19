/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:18:09 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/10/18 16:24:18 by tiagoliv         ###   ########.fr       */
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
void	init_event_handlers(t_win *win);

// map.c
t_bool	check_args(int argc, char *argv[]);

#endif