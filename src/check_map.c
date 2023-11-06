/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:29:18 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/11/06 18:24:47 by tiagoliv         ###   ########.fr       */
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
		ft_printf(MSG_INVALID_MAP_NAME);
		return (NULL);
	}
	width = 0;
	height = 0;
	error = get_map_size(fd, &width, &height);
	read_everything_fd(fd);
	close(fd);
	if ((width <= 1 || height <= 1) || error != NO_ERROR)
	{
		if (width <= 1 || height <= 1)
			error = INVALID_MAP_STRUCTURE;
		put_error(error, NULL);
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
	map->height = height;
	map->items = 0;
	map->map = malloc(sizeof(char *) * map->height);
	if (!map->map)
		return (NULL);
	index = 0;
	while (index < map->height)
	{

		map->map[index] = malloc(sizeof(char) * (width + 1));
		if (!map->map[index])
			return (NULL);
		ft_bzero(map->map[index], width + 1);
		index++;
	}

	return (map);
}

void	update_map(t_so_long *so_long)
{
	int	x;
	int	y;

	if (!map_has_correct_identifiers(so_long->game->map))
		close_win(so_long);
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
	if (!map_has_proper_walls(so_long->game->map) || \
		!map_has_valid_path(so_long->game->map, so_long->game->player->coords))
		close_win(so_long);
}

t_bool	copy_map(t_map *m_src, t_map *m_dest)
{
	int	x;
	int	y;
	
	if (m_src->height != m_dest->height || m_src->width != m_dest->width)
		return (false);
	y = 0;
	while (y < m_src->height)
	{
		x = 0;
		while (x < m_src->width)
		{
			m_dest->map[y][x] = m_src->map[y][x];
			x++;
		}
		y++;
	}
	return (true);
}

void	read_everything_fd(int fd)
{
	char *line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

