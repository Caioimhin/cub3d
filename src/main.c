/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:31:57 by kparis            #+#    #+#             */
/*   Updated: 2020/02/10 15:50:42 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include <fcntl.h>

int		main(int ac, char **av)
{
	int fd;
	t_map map;
	t_mlx data;

	data.map = &map;
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
	mlx_string_put(data.mlx, data.window, (map.res_x/2), (map.res_y/2), map.floor, data.map->sprite);
	//prendre un screen si besoin
	//hook des touches
	mlx_hook(data.window, 17, 0, close_cub, &data);
	mlx_hook(data.window, 2, 1L<<0, handle_keypress, &data);
	//loop
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}