/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:17:42 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/11/02 14:47:12 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char **argv)
{
	t_so_long	*so_long;

	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	so_long = so_long_init(argv[1]);
	if (!so_long)
		close_win(so_long);
	render_map(so_long->win, so_long->game);
	init_event_handlers(so_long);

	mlx_loop(so_long->win->mlx);
	return (EXIT_SUCCESS);
}

t_win	*win_init(int width, int height)
{
	t_win	*win;

	win = malloc(sizeof(t_win));
	if (!win)
		return (NULL);
	win->mlx = mlx_init();
	if (!win->mlx)
		return (NULL);
	win->win = mlx_new_window(win->mlx, width * IMAGE_SIZE, height * IMAGE_SIZE, "so_long");
	if (!win->win)
		return (NULL);
	return (win);
}

t_so_long	*so_long_init(char *map_path)
{
	t_so_long	*so_long;	

	so_long = malloc(sizeof(t_so_long));
	if (!so_long)
		close_win(so_long);
	so_long->win = NULL;
	so_long->game = malloc(sizeof(t_game));
	if (!so_long->game)
		close_win(so_long);
	so_long->game->player = NULL;
	so_long->game->assets = NULL;
	so_long->game->map = check_map(map_path);
	if (!so_long->game->map)
		close_win(so_long);
	update_map(so_long);
	so_long->win = win_init(so_long->game->map->width, so_long->game->map->height);
	so_long->game->assets = load_assets(so_long->win->mlx);
	if (!so_long->game->assets)
		close_win(so_long);

	return (so_long);
}
