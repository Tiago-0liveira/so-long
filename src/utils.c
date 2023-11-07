/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:52:02 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/11/07 13:26:03 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_bool	ends_with(char *str, char *end)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(end) - 1;
	while (j >= 0)
	{
		if (str[i] != end[j])
			return (false);
		i--;
		j--;
	}
	return (true);
}

void	free_win(t_win *win)
{
	if (win)
	{
		if (win->win)
			mlx_destroy_window(win->mlx, win->win);
		if (win->mlx)
		{
			mlx_destroy_display(win->mlx);
			free(win->mlx);
		}
		free(win);
	}
}

void	close_win(t_so_long *so_long)
{
	if (!so_long->win)
		free_game(NULL, so_long->game);
	else
		free_game(so_long->win->mlx, so_long->game);
	free_win(so_long->win);
	free(so_long);
	exit(EXIT_SUCCESS);
}

void	free_game(void *mlx, t_game *game)
{
	if (game)
	{
		if (game->map)
			free_map(game->map);
		if (game->assets && mlx)
			free_assets(mlx, game->assets);
		if (game->player)
			free(game->player);
		free(game);
	}
}

int	char_count(char *str, int c)
{
	int	x;
	int	count;

	x = 0;
	count = 0;
	while (str[x] != '\0')
	{
		if (str[x] == c)
			count++;
		x++;
	}
	return (count);
}
