/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eventHandlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:44:03 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/11/07 13:20:47 by tiagoliv         ###   ########.fr       */
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

	moved = false;
	if (keycode == K_W || keycode == K_UP)
		moved = move_player(so_long, UP);
	else if (keycode == K_A || keycode == K_LEFT)
		moved = move_player(so_long, LEFT);
	else if (keycode == K_S || keycode == K_DOWN)
		moved = move_player(so_long, DOWN);
	else if (keycode == K_D || keycode == K_RIGHT)
		moved = move_player(so_long, RIGHT);
	else if (keycode == K_ESC)
		close_win(so_long);
	if (moved)
		ft_printf("moves: %d\n", so_long->game->player->moves);
	return (0);
}
