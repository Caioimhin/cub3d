/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 11:30:25 by kparis            #+#    #+#             */
/*   Updated: 2020/03/27 17:40:20 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_rgb(int r, int g, int b)
{
	int	rgb;

	rgb = r;
	rgb = (rgb << 8) + g;
	rgb = (rgb << 8) + b;
	return (rgb);
}

void	get_img_adrr(t_mlx *data)
{
	data->img->adress = mlx_get_data_addr(data->img->img_ptr, &data->img->bits_per_pxl, &data->img->line_length, &data->img->endian);
}

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->adress + (y * img->line_length + x * (img->bits_per_pxl / 8));
	*(unsigned int*)dst = color;
}

int		close_mlx(t_mlx *data)
{
	mlx_destroy_window(data->mlx, data->window);
	exit(0);
	return (EXIT_SUCCESS);
}