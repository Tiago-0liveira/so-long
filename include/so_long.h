/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:18:09 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/10/09 14:00:32 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include "../../../mlx_linux/mlx.h"
# include "../42-libft/libft.h"

typedef struct win_t {
    void *mlx;
    void *win;
} win_t;

enum HOOKING_EVENT {
    KeyPress = 2,
    DestroyNotif = 17,
};

enum EventMask {
	NoEventMask = (0L),
    KeyPressMask = (1L<<0)
};

enum KeyCode {
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
void    init_event_handlers(win_t *win);

#endif