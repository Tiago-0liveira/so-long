/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:29:18 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/11/02 16:13:15 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_map	*check_map(char *path)
{
	int						fd;
	enum e_map_check_error	error;
	int						height;
	int						width;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(MSG_INVALID_MAP_PATH);
		return (NULL);
	}
	width = 0;
	height = 0;
	error = get_map_size(fd, &width, &height);
	close(fd);
	if (error != NO_ERROR)
	{
		if (error == INVALID_MAP_DIMENSIONS)
			ft_printf(MSG_INVALID_MAP_DIMENSIONS);
		else if (error == INVALID_MAP_IDENTIFIER)
			ft_printf(MSG_INVALID_MAP_IDENTIFIER);
		return (NULL);
	}
	return (load_map(path, &width, &height));
}

t_map	*map_init(int width, int height)
{
	t_map	*map;
	int		index;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = width;
	map->height = height + 1;
	map->map = malloc(sizeof(char *) * map->height);
	if (!map->map)
		return (NULL);
	index = 0;
	while (index < map->height)
	{
		map->map[index] = malloc(sizeof(char) * (width + 1));
		if (!map->map[index])
			return (NULL);
		ft_bzero(map->map[index], width);
		index++;
	}

	return (map);
}

t_bool	map_has_valid_path(t_map *map)
{
	(void)map;
	return (true);
}

t_bool	map_has_correct_identifiers(t_map *map)
{
	int	player;
	int	exit;
	int	items;
	int	x;
	int	y;

	player = 0;
	exit = 0;
	items = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == PLAYER)
				player++;
			else if (map->map[y][x] == ITEM)
				items++;
			if (map->map[y][x] == EXIT)
				exit++;
			x++;
		}
		y++;
	}

	return (player == 1 && exit == 1 && items >= 1);
}

void	update_map(t_so_long *so_long)
{
	int	x;
	int	y;

	ft_printf("jereererer\n");
	if (!map_has_valid_path(so_long->game->map) || \
		!map_has_correct_identifiers(so_long->game->map) || \
		!map_has_proper_walls(so_long->game->map))
		close_win(so_long);
	ft_printf("jereerereaddas121213sr\n");
	x = 0;
	while (x < so_long->game->map->height)
	{
		y = 0;
		while (y < so_long->game->map->width)
		{
			if (so_long->game->map->map[x][y] == PLAYER)
			{
				so_long->game->player = player_init(y, x);
				if (!so_long->game->player)
					close_win(so_long);
				so_long->game->map->map[x][y] = EMPTY;
			}
			y++;
		}
		x++;
	}
}
