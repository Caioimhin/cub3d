/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 10:30:10 by kparis            #+#    #+#             */
/*   Updated: 2020/03/29 01:47:45 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_message(char *text)
{
	ft_putendl("Error");
	ft_putstr(text);
	exit(0);
}

int		check_args(int ac, char **av, t_mlx *data)
{
	if (ac < 2 || ac > 3)
		error_message("Invalid arguments number");
	else
	{
		if (ac == 3 && ft_strncmp(av[1], "--save", 6) == 0)
		{
			data->map->cub_path = av[2];
			return (1);
		}
		else if (ac == 3 && ft_strncmp(av[1], "--save", 6) != 0)
			error_message("Invalid argument");
	}
	data->map->cub_path = av[1];
	return (0);
}

int		main(int ac, char **av)
{
	t_map	map;
	t_img	img;
	t_ray	ray;
	t_mlx	data;

	data.map = &map;
	data.img = &img;
	data.ray = &ray;
	data.map->save = check_args(ac, av, &data);
	parse_cub_args(&data);
	//mlx init//
	if (!(data.mlx = mlx_init()))
		error_message("Can't init mlx");
	data.window = mlx_new_window(data.mlx, map.res_x, map.res_y, "Cub3d");
	data.img->img_ptr = mlx_new_image(data.mlx, map.res_x, map.res_y);
	get_img_adrr(&data);
	mlx_hook(data.window, 17, 0, close_mlx, &data);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_loop(data.mlx);
	return (0);
}
