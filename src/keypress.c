/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:04:04 by kparis            #+#    #+#             */
/*   Updated: 2020/02/13 12:31:47 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keycode, t_mlx *data)
{
	(keycode == ESC) ? close_cub(data) : 0;
	(keycode == UP) ? data->key->key_up = 1 : 0;
	(keycode == DOWN) ? data->key->key_down = 1 : 0;
	(keycode == LEFT) ? data->key->key_left = 1 : 0;
	(keycode == RIGHT) ? data->key->key_right = 1 : 0;
	return (0);
}

int	handle_keyrelease(int keycode, t_mlx *data)
{
	(keycode == UP) ? data->key->key_up = 0 : 0;
	(keycode == DOWN) ? data->key->key_down = 0 : 0;
	(keycode == LEFT) ? data->key->key_left = 0 : 0;
	(keycode == RIGHT) ? data->key->key_right = 0 : 0;
	return (0);
}