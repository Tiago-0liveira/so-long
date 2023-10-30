/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:56:59 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/10/27 21:28:49 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_xpm_image	*load_xpm_img(void *mlx, char *path)
{
	t_xpm_image	*xpm_img;

	xpm_img = malloc(sizeof(t_xpm_image));
	if (!xpm_img)
		return (NULL);
	xpm_img->p_img = mlx_xpm_file_to_image(mlx, path, &xpm_img->width,
			&xpm_img->height);
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
	assets->wall = load_xpm_img(mlx, WALL_PATH);
	assets->ground = load_xpm_img(mlx, GROUND_PATH);
	assets->player = load_xpm_img(mlx, PLAYER_PATH);
	assets->item = load_xpm_img(mlx, ITEM_PATH);
	assets->exit = load_xpm_img(mlx, EXIT_PATH);
	if (!assets->wall || !assets->ground || !assets->player || !assets->item
		|| !assets->exit)
	{
		free_assets(mlx, assets);
		return (NULL);
	}
	return (assets);
}

void	render_map(t_win *win, t_game *game)
{
	int						i;
	int						j;
	enum e_map_identifiers	identifier;
	t_xpm_image				*img;

	mlx_clear_window(win->mlx, win->win);
	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			identifier = get_identifier(game->map->map[i][j]);
			mlx_put_image_to_window(win->mlx, win->win,
				game->assets->ground->p_img, j * IMAGE_SIZE, i * IMAGE_SIZE);
			if (identifier != EMPTY)
			{
				img = get_img_from_identifier(game->assets, identifier);
				mlx_put_image_to_window(win->mlx, win->win, img->p_img, j
					* img->width, i * img->height);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(win->mlx, win->win, game->assets->player->p_img,
		game->player->x * IMAGE_SIZE, game->player->y * IMAGE_SIZE);
	ft_printf("just rendered everything\n");
}

void	free_xpm_img(void *mlx, t_xpm_image *img)
{
	if (img)
	{
		if (img->p_img)
			mlx_destroy_image(mlx, img->p_img);
		free(img);
	}
}

void	free_assets(void *mlx, t_assets *assets)
{
	if (assets)
	{
		if (assets->wall)
			free_xpm_img(mlx, assets->wall);
		if (assets->ground)
			free_xpm_img(mlx, assets->ground);
		if (assets->player)
			free_xpm_img(mlx, assets->player);
		if (assets->item)
			free_xpm_img(mlx, assets->item);
		if (assets->exit)
			free_xpm_img(mlx, assets->exit);
		free(assets);
	}
}
