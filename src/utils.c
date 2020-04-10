/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 11:30:25 by kparis            #+#    #+#             */
/*   Updated: 2020/04/10 04:25:11 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear(t_mlx *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->map->res_y)
	{
		x = 0;
		while (x < data->map->res_x)
		{
			ft_mlx_pixel_put(data->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

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
	dst = (char *)img->colors + (y * img->line_length + x * (img->bits_per_pxl / 8));
	*(int*)dst = color;
}

int		close_mlx(t_mlx *data)
{
	mlx_destroy_window(data->mlx, data->window);
	exit(0);
	return (EXIT_SUCCESS);
}

void	create_texture_img(t_mlx *data, char *path, t_img *text)
{
	text->img_ptr = mlx_xpm_file_to_image(data->mlx, path, &text->x, &text->y);
	if (text->img_ptr == NULL)
		close_mlx(data);
	text->colors = (int*)mlx_get_data_addr(text->img_ptr, &text->bits_per_pxl,&text->line_length, &text->endian);
}