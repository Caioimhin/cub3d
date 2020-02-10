/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 12:04:05 by kparis            #+#    #+#             */
/*   Updated: 2020/02/10 15:49:54 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	get_img_adrr(t_mlx &data)
// {
// 	data->img->adress = mlx_get_data_addr(data->img->img, &data->img->bits_per_pxl, &data->img->line_length, &data->img->endian);
// }

// void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = img->adress + (y * img->line_length + x * (img->bits_per_pxl / 8));
// 	*(unsigned int*)dst = color;
// }

int close_cub(t_mlx *data)
{
	int i;

	i = 0;
	while (data->map->map[i])
		free(data->map->map[i++]);
	free(data->map->map);
	exit(EXIT_SUCCESS);
}