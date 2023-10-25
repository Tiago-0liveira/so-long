/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:17:42 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/10/19 17:18:57 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(void)
{
	t_win	*win;
	t_game	*game;

	win = malloc(sizeof(t_win));
	if (!win)
		return (EXIT_FAILURE);
	win->mlx = mlx_init();
	win->win = mlx_new_window(win->mlx, 1280, 920, "Hello world!");

	game = malloc(sizeof(game));
	if (!game)
		return (EXIT_FAILURE);
	game->assets = load_assets(win->mlx);
	if (!game->assets)
		return (EXIT_FAILURE);
	render_assets(win, game->assets);
	init_event_handlers(win);

	mlx_loop(win->mlx);
	return (EXIT_SUCCESS);
}
