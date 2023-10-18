/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventHandlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:44:03 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/10/18 16:23:33 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	key_press(int keycode, t_win *win);
static int	close_win(t_win *win);

void	init_event_handlers(t_win *win)
{
    mlx_hook(win->win, KeyPress, KeyPressMask, key_press, win);
    mlx_hook(win->win, DestroyNotify, KeyPressMask, close_win, win);
}

static int	close_win(t_win *win)
{
    if (win)
    {
        if (win->win)
            mlx_destroy_window(win->mlx, win->win);
        if (win->mlx)
        {
            mlx_destroy_display(win->mlx);
            free(win->mlx);
        }
        free(win);
    }
    exit(0);
}

static int	key_press(int keycode, t_win *win)
{
    ft_printf("key_press\n");
    if (keycode == W || keycode == UP)
        ft_printf("up");
    else if (keycode == A || keycode == LEFT)
        ft_printf("left");
    else if (keycode == S || keycode == DOWN)
        ft_printf("down");
    else if (keycode == D || keycode == RIGHT)
        ft_printf("right");
    else if (keycode == ESC)
        close_win(win);
    else
    {
        ft_printf("debug|keycode:%d\n", keycode);
    }
    return (0);
}
