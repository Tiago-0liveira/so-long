/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:19:42 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/10/27 21:43:55 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_player	*player_init(int x, int y)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->x = x;
	player->y = y;
	player->moves = 0;
	player->items = 0;
	return (player);
}

t_bool	player_can_move(t_game *game, enum e_player_direction dir)
{
	int	x;
	int	y;

	x = game->player->x;
	y = game->player->y;
	set_dir_value(dir, &x, &y);
	ft_printf("player_can_move:%c\n", game->map->map[y][x]);
	if (x <= 0 || y <= 0 || x >= game->map->width || y >= game->map->height)
		return (false);
	return (game->map->map[y][x] != WALL);
}

void	set_dir_value(enum e_player_direction dir, int *x, int *y)
{
	if (dir == UP)
		(*y)--;
	else if (dir == DOWN)
		(*y)++;
	else if (dir == LEFT)
		(*x)--;
	else if (dir == RIGHT)
		(*x)++;
}

t_bool	move_player(t_so_long *so_long, enum e_player_direction dir)
{
	enum e_map_identifiers	identifier;

	
	if (player_can_move(so_long->game, dir))
	{
		ft_printf("Player move:x:%d y:%d\n", so_long->game->player->x, so_long->game->player->y);
		identifier = so_long->game->map->map[so_long->game->player->y]
		[so_long->game->player->x];
		so_long->game->player->moves++;
		set_dir_value(dir, &so_long->game->player->x, \
		&so_long->game->player->y);
		ft_printf("Player move2:x:%d y:%d\n", so_long->game->player->x, so_long->game->player->y);
		if (identifier == ITEM)
		{
			so_long->game->player->items++;
			so_long->game->map->map[so_long->game->player->y]
			[so_long->game->player->x] = EMPTY;
		}
		else if (identifier == EXIT)
		{
			ft_printf("end game\n"); //TODO: end game
			close_win(so_long);
		}
		return (true);
	}
	return (false);
}
