/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 17:35:56 by kparis            #+#    #+#             */
/*   Updated: 2020/03/27 17:40:20 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		raycasting(t_mlx *data)
{
	ft_mlx_pixel_put(data->img, 50, 50, 0x00FF0000);
	mlx_put_image_to_window(data->mlx, data->window, data->img->img_ptr, 0, 0);
	return (EXIT_SUCCESS);
}