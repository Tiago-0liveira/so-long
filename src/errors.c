/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiagoliv <tiagoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:56:23 by tiagoliv          #+#    #+#             */
/*   Updated: 2023/11/07 13:21:06 by tiagoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	put_error(enum e_map_check_error error, t_so_long *so_long)
{
	if (error == INVALID_MAP_DIMENSIONS)
		ft_printf(MSG_INVALID_MAP_DIMENSIONS);
	else if (error == INVALID_MAP_IDENTIFIER)
		ft_printf(MSG_INVALID_MAP_IDENTIFIER);
	else if (error == MAP_NOT_FOUND)
		ft_printf(MSG_INVALID_MAP_NAME);
	else if (error == INVALID_MAP_EXTENSION)
		ft_printf(MSG_INVALID_MAP_FILE_EXTENSION);
	else if (error == INVALID_PATH)
		ft_printf(MSG_INVALID_MAP_PATH);
	else if (error == INVALID_MAP_STRUCTURE)
		ft_printf(MSG_INVALID_MAP_STRUCTURE);
	if (so_long)
		close_win(so_long);
}

t_map_checker	init_map_checker(void)
{
	t_map_checker	mc;

	mc.player = 0;
	mc.exit = 0;
	mc.items = 0;
	mc.x = 0;
	mc.y = 0;
	return (mc);
}
