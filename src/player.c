/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 21:19:42 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/11/07 13:28:33 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_player	*player_init(int x, int y)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->coords = (t_point){x, y};
	player->moves = 0;
	player->items = 0;
	return (player);
}

t_bool	player_can_move(t_game *game, enum e_player_direction dir)
{
	t_point	coords;

	coords = (t_point){game->player->coords.x, game->player->coords.y};
	apply_dir_value(dir, &coords);
	if (coords.x <= 0 || coords.y <= 0 || coords.x >= game->map->width
		|| coords.y >= game->map->height)
		return (false);
	return (game->map->map[coords.y][coords.x] != WALL);
}

void	apply_dir_value(enum e_player_direction dir, t_point *coords)
{
	if (dir == UP)
		(coords->y)--;
	else if (dir == DOWN)
		(coords->y)++;
	else if (dir == LEFT)
		(coords->x)--;
	else if (dir == RIGHT)
		(coords->x)++;
}

t_bool	move_player(t_so_long *so_long, enum e_player_direction dir)
{
	enum e_map_identifiers	identifier;

	if (player_can_move(so_long->game, dir))
	{
		so_long->game->player->moves++;
		apply_dir_value(dir, &so_long->game->player->coords);
		identifier = so_long->game->map->map[so_long->game->player->coords.y] \
			[so_long->game->player->coords.x];
		if (identifier == ITEM)
		{
			so_long->game->player->items++;
			so_long->game->map->map[so_long->game->player->coords.y] \
				[so_long->game->player->coords.x] = EMPTY;
		}
		render_map(so_long->win, so_long->game);
		if (identifier == EXIT && so_long->game->map->items == \
			so_long->game->player->items)
		{
			ft_printf("moves: %d\n", so_long->game->player->moves);
			ft_printf("You won!\n");
			close_win(so_long);
		}
		return (true);
	}
	return (false);
}
