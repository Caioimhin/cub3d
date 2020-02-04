/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:31:57 by kparis            #+#    #+#             */
/*   Updated: 2020/02/04 15:41:53 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"

int main(void)
{
	t_mlx data;
	t_img img;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, 600, 600, "Cub3d");
	img.img = mlx_new_image(data.mlx, 600, 600);
	img.adress = mlx_get_data_addr(img.img, &img.bits_per_pxl, &img.line_length, &img.endian);
	clear_screen(&img, 600, 600);
	mlx_put_image_to_window(data.mlx, data.window, img.img, 0, 0);
	mlx_hook(data.window, 17, 0, close, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}

int		close()
{
	exit(0);
}

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->adress + (y * img->line_length + x * (img->bits_per_pxl / 8));
	*(unsigned int*)dst = color;
}

void	clear_screen(t_img *img, int x_max, int y_max)
{
	int x;
	int y;

	y = 0;
	while (y < y_max)
	{
		x = 0;
		while (x < x_max)
		{
			ft_mlx_pixel_put(img, x, y, 0x00FFFFFF);
			x += 1;
		}
		y += 1;
	}
	img->img_cpy = img->img;
}