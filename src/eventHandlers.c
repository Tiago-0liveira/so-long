/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventHandlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:44:03 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/10/27 21:42:48 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	key_press(int keycode, t_so_long *so_long);
static int	handle_close(t_so_long *so_long);

void	init_event_handlers(t_so_long *so_long)
{
	mlx_hook(so_long->win->win, KeyPress, KeyPressMask, key_press, so_long);
	mlx_hook(so_long->win->win, DestroyNotify, KeyPressMask, handle_close,
		so_long);
}

static int	handle_close(t_so_long *so_long)
{
	close_win(so_long);
	return (0);
}

static int	key_press(int keycode, t_so_long *so_long)
{
	t_bool	moved;

	ft_printf("key_press\n");
	if (keycode == K_W || keycode == K_UP)
	{
		ft_printf("key_press|up\n");
		moved = move_player(so_long, UP);
	}
	else if (keycode == K_A || keycode == K_LEFT)
	{
		ft_printf("key_press|left");
		moved = move_player(so_long, LEFT);
	}
	else if (keycode == K_S || keycode == K_DOWN)
	{
		ft_printf("key_press|down");
		moved = move_player(so_long, DOWN);
	}
	else if (keycode == K_D || keycode == K_RIGHT)
	{
		ft_printf("key_press|right");
		moved = move_player(so_long, DOWN);
	}
	else if (keycode == K_ESC)
		close_win(so_long);
	else
	{
		ft_printf("debug|keycode:%d\n", keycode);
	}
	if (moved)
		render_map(so_long->win, so_long->game);
	return (0);
}
