/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:17:42 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/10/09 14:00:39 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int main()
{
    win_t win;

    win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, 1280, 920, "Hello world!");

    init_event_handlers(&win);

    return 0;
}