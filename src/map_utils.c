/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:49:15 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/11/02 16:12:26 by tiagoliv         ###   ########.fr       */
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
