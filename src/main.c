/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:31:57 by kparis            #+#    #+#             */
/*   Updated: 2020/02/14 15:09:42 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include <fcntl.h>

int		main(int ac, char **av)
{
	int fd;
	t_map map;
	t_key key;
	t_img img;
	t_player player;
	t_mlx data;


	data.map = &map;
	data.key = &key;
	data.img = &img;
	data.player = &player;
	data.key->key_up = 0;
	data.key->key_down = 0;
	data.key->key_left = 0;
	data.key->key_right = 0;
	data.key->key_turnleft = 0;
	data.key->key_turnright = 0;
	data.key->key_esc = 0;
	//checker le nb d'arguments
	if (ac < 2 || ac > 4)
	{
		ft_putstr("Error\nWrong number of arguments");
		exit(0);
	}
	if (ac == 3)
	{
		if (ft_strncmp("-save", av[1], ft_strlen("-save")) != 0)
		{
			ft_putstr("Error\nWrong arguments order");
			exit(0);
		}
	}
	fd = (ac == 2) ?  open(av[1], O_RDONLY) : open(av[2], O_RDONLY);
	parse_map(data.map, fd);
	close(fd);
	//afficher la premiere image
	if (!(data.mlx = mlx_init()))
	{
		ft_putstr("Error\nCouldn't init MLX pointer.");
		return(EXIT_FAILURE);
	}
	data.window = mlx_new_window(data.mlx, map.res_x, map.res_y, "Cub3d");
	//prendre un screen si besoin
	//hook des touches
	data.img->img = mlx_new_image(data.mlx, map.res_x, map.res_y);
	get_img_adrr(&data);
	int x, y = 0;

	while (y < data.map->res_y)
	{
		x = 0;
		while (x < data.map->res_x)
		{
			ft_mlx_pixel_put(data.img, x, y, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data.mlx, data.window, data.img->img, 0, 0);

	raycasting(&data);
	//loop
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
