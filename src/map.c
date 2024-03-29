/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:12:54 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/11/07 15:04:00 by tiagoliv         ###   ########.fr       */
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
		ft_printf(MSG_INVALID_MAP_FILE_EXTENSION);
		return (false);
	}
	return (true);
}

t_bool	is_valid_identifier(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

t_xpm_image	*get_img(t_assets *assets, enum e_map_identifiers identifier)
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

t_map	*load_map(int fd, int *width, int *height)
{
	int		index;
	char	*line;
	t_map	*map;

	map = map_init(*width, (*height) + 1);
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	line = get_next_line(fd);
	while (line)
	{
		index = 0;
		while (line[index] && line[index] != '\n')
		{
			map->map[map->height - (*height) - 1][index] = line[index];
			index++;
		}
		free(line);
		line = get_next_line(fd);
		(*height)--;
	}
	close(fd);
	return (map);
}
