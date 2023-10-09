/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventHandlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:44:03 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/10/09 15:46:15 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static  int win_close(int keycode, win_t *win);
static  int key_press(int keycode, win_t *win);

void    init_event_handlers(win_t *win)
{
    mlx_hook(win->win, DestroyNotif, NoEventMask, win_close, win);
    mlx_hook(win->win, KeyPress, KeyPressMask, key_press, win);
    mlx_loop(win->mlx);
}

static int win_close(int keycode, win_t *win)
{
    (void)keycode;
    mlx_destroy_window(win->mlx, win->win);
    mlx_destroy_display(win->mlx);
    free(win->mlx);
    exit(0);
}

static  int key_press(int keycode, win_t *win)
{
    if (keycode == W || keycode == UP)
        ft_printf("up");
    else if (keycode == A || keycode == LEFT)
        ft_printf("left");
    else if (keycode == S || keycode == DOWN)
        ft_printf("down");
    else if (keycode == D || keycode == RIGHT)
        ft_printf("right");
    else if (keycode == ESC)
        win_close(keycode, win);
    return (0);
}
