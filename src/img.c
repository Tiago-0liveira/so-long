/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:56:59 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/10/20 02:00:02 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_xpm_image	*load_xpm_img(void *mlx, char *path)
{
	t_xpm_image	*xpm_img;

	xpm_img = malloc(sizeof(t_xpm_image));
	if (!xpm_img)
		return (NULL);
	xpm_img->p_img = mlx_xpm_file_to_image(mlx, path, \
		&xpm_img->width, &xpm_img->height);
	if (!xpm_img->p_img)
	{
		/* TODO: remove in the future */
		printf("Could not load %s image!\n", path);
		free(xpm_img);
		return (NULL);
	}
	return (xpm_img);
}

t_assets	*load_assets(void *mlx)
{
	t_assets	*assets;

	assets = malloc(sizeof(t_assets));
	if (!assets)
		return (NULL);
	
	assets->knight = load_xpm_img(mlx, KNIGHT_PATH);
	assets->leaves = load_xpm_img(mlx, LEAVES_PATH);
	assets->walkstone = load_xpm_img(mlx, WALKSTONE_PATH);
	if (!assets->knight || !assets->leaves || !assets->walkstone)
	{
		free_assets(mlx, &assets);
		return (NULL);
	}
	return (assets);
}

void	render_assets(t_win *win, t_assets *assets)
{
	printf("%p|%p|%p\n", win->mlx, win->win, assets->leaves->p_img);
	mlx_put_image_to_window(win->mlx, win->win, \
		assets->leaves->p_img, 0, 0);
	mlx_put_image_to_window(win->mlx, win->win, \
		assets->walkstone->p_img, 64, 64);
	mlx_put_image_to_window(win->mlx, win->win, \
		assets->knight->p_img, 128, 128);
}

void	free_xpm_img(void *mlx, t_xpm_image **img)
{
	if (*img)
	{
		if ((*img)->p_img)
			mlx_destroy_image(mlx, (*img)->p_img);
		free(*img);
	}
}

void	free_assets(void *mlx, t_assets	**assets)
{
	if (*assets)
	{
		if (!(*assets)->knight)
			free_xpm_img(mlx, &(*assets)->knight);
		if (!(*assets)->leaves)
			free_xpm_img(mlx, &(*assets)->leaves);
		if (!(*assets)->walkstone)
			free_xpm_img(mlx, &(*assets)->walkstone);
		free(*assets);
	}
}
