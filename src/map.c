/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:12:54 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/10/26 22:23:25 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_bool	check_args(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_printf(USAGE);
		return (false);
	}
	else if (!ends_with(argv[1], MAP_FILE_EXTENSION))
	{
		ft_printf("Invalid map file extension!\n");
		return (false);
	}
	return (true);
}

enum e_map_identifiers	get_identifier(char c)
{
	if (c == '0')
		return (EMPTY);
	else if (c == '1')
		return (WALL);
	else if (c == 'C')
		return (ITEM);
	else if (c == 'E')
		return (EXIT);
	else if (c == 'P')
		return (PLAYER);
	else
		return (INVALID);
}

t_bool	is_valid_identifier(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

t_xpm_image	*get_img_from_identifier( \
	t_assets *assets, enum e_map_identifiers identifier)
{
	if (identifier == WALL)
		return (assets->wall);
	else if (identifier == ITEM)
		return (assets->item);
	else if (identifier == EXIT)
		return (assets->exit);
	else if (identifier == PLAYER)
		return (assets->player);
	else if (identifier == EMPTY)
		return (assets->ground);
	else
		return (NULL);
}

enum e_map_check_error	get_map_size(int fd, int *width, int *height)
{
	char	*line;
	int		index;

	line = get_next_line(fd);
	while (line)
	{
		index = 0;
		while (line[index] && line[index] != '\n')
		{
			if (!is_valid_identifier(line[index]))
			{
				free(line);
				return (INVALID_MAP_IDENTIFIER);
			}
			index++;
		}
		free(line);
		if (*width != index && *width != 0)
			return (INVALID_MAP_DIMENSIONS);
		*width = index;
		(*height)++;
		line = get_next_line(fd);
	}
	(*height)--;
	return (NO_ERROR);
}

t_map	*load_map(char *path, int *width, int *height)
{
	int		fd;
	int		index;
	char	*line;
	t_map	*map;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = map_init(*width, *height);
	if (!map)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		index = 0;
		while (line[index] && line[index] != '\n')
		{
			map->map[map->height - *height - 1][index] = line[index];
			index++;
		}
		free(line);
		line = get_next_line(fd);
		(*height)--;
	}
	return (map);
}

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

void	update_map(t_so_long *so_long)
{
	/* TODO: check PATH, check walls, check items number */
	int	x;
	int	y;

	x = 0;
	while (x < so_long->game->map->height)
	{
		y = 0;
		while (y < so_long->game->map->width)
		{
			if (so_long->game->map->map[x][y] == 'P')
			{
				so_long->game->player = player_init(y, x);
				if (!so_long->game->player)
					close_win(so_long);
				so_long->game->map->map[x][y] = '0';
			}
			y++;
		}
		x++;
	}
}
