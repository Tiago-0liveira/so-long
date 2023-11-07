/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:49:15 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/11/07 13:25:59 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_bool	map_has_proper_walls(t_map	*map)
{
	int	x;

	if (char_count(map->map[0], WALL) != map->width || \
		char_count(map->map[map->height - 1], WALL) != map->width)
	{
		ft_printf(MSG_INVALID_WALLS);
		return (false);
	}
	x = 0;
	while (x < map->height)
	{
		if (map->map[x][0] != WALL || map->map[x][map->width - 1] != WALL)
		{
			ft_printf(MSG_INVALID_WALLS);
			return (false);
		}
		x++;
	}
	return (true);
}

void	free_map(t_map *map)
{
	if (map)
	{
		if (map->map)
		{
			while (map->height--)
				free(map->map[map->height]);
			free(map->map);
		}
		free(map);
	}
}

t_bool	map_has_valid_path(t_map *map, t_point p_coords)
{
	t_map	*sol_map;

	sol_map = map_init(map->width, map->height);
	if (!sol_map)
	{
		free_map(sol_map);
		return (false);
	}
	if (!copy_map(map, sol_map))
	{
		free_map(sol_map);
		return (false);
	}
	if (!sol_map_fill(map, p_coords, sol_map))
	{
		ft_printf(MSG_INVALID_MAP_PATH);
		free_map(sol_map);
		return (false);
	}
	free_map(sol_map);
	return (true);
}

t_bool	sol_map_fill(t_map *map, t_point current, t_map *sol_map)
{
	static t_bool	exit_found = false;
	static int		items = 0;

	if (sol_map->map[current.y][current.x] == WALL)
		return (false);
	else if (sol_map->map[current.y][current.x] == EXIT)
		exit_found = true;
	else if (sol_map->map[current.y][current.x] == ITEM)
		items++;
	sol_map->map[current.y][current.x] = WALL;
	sol_map_fill(map, (t_point){current.x + 1, current.y}, sol_map);
	sol_map_fill(map, (t_point){current.x - 1, current.y}, sol_map);
	sol_map_fill(map, (t_point){current.x, current.y + 1}, sol_map);
	sol_map_fill(map, (t_point){current.x, current.y - 1}, sol_map);
	return (map->items == items && exit_found);
}

t_bool	map_has_correct_identifiers(t_map *map)
{
	t_map_checker	mc;

	mc = init_map_checker();
	while (mc.y < map->height)
	{
		mc.x = 0;
		while (mc.x < map->width)
		{
			if (map->map[mc.y][mc.x] == PLAYER)
				mc.player++;
			if (map->map[mc.y][mc.x] == ITEM)
				mc.items++;
			if (map->map[mc.y][mc.x] == ITEM)
				map->items++;
			if (map->map[mc.y][mc.x] == EXIT)
				mc.exit++;
			mc.x++;
		}
		mc.y++;
	}
	if (!(mc.player == 1 && mc.exit == 1 && mc.items >= 1))
		put_error(INVALID_MAP_STRUCTURE, NULL);
	return (mc.player == 1 && mc.exit == 1 && mc.items >= 1);
}
