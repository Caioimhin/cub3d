/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 16:20:16 by kparis            #+#    #+#             */
/*   Updated: 2020/03/31 16:39:02 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		keyrelease(int keycode, t_mlx *data)
{
	if (keycode == UP)
		data->k_up = 0;
	else if (keycode == DOWN)
		data->k_down = 0;
	else if (keycode == LEFT)
		data->k_left = 0;
	else if (keycode == RIGHT)
		data->k_right = 0;
	else if (keycode == TURN_LEFT)
		data->k_turn_left = 0;
	else if (keycode == TURN_RIGHT)
		data->k_turn_right = 0;
	return (0);
}

int		keypress(int keycode, t_mlx *data)
{
	if (keycode == UP)
		data->k_up = 1;
	else if (keycode == DOWN)
		data->k_down = 1;
	else if (keycode == LEFT)
		data->k_left = 1;
	else if (keycode == RIGHT)
		data->k_right = 1;
	else if (keycode == TURN_LEFT)
		data->k_turn_left = 1;
	else if (keycode == TURN_RIGHT)
		data->k_turn_right = 1;
	else if (keycode == ESC)
		close_mlx(data);
	return (0);
}