/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:57:06 by kparis            #+#    #+#             */
/*   Updated: 2020/06/22 15:07:33 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wrong_args(char *msg)
{
	ft_putendl(msg);
	exit(0);
}

void	check_args_errors(t_data *data, int argc, char **argv)
{
	if (argc == 1 || argc > 3)
		wrong_args("Invalid arguments number");
	if (argc == 3 && ft_memcmp(argv[1], "--save", 6))
		wrong_args("--save is not the second argument");
	else if (argc == 3)
		data->save = 1;
	else
		data->save = 0;
	if (argc == 3)
	{
		if (ft_memcmp(&argv[2][ft_strlen(argv[2]) - 4], ".cub", 4))
			wrong_args("Invalid file extension");
		if ((data->maps.fd = open(argv[2], O_RDONLY)) == -1)
			wrong_args("Couldn't open .cub file");
	}
	else
	{
		if (ft_memcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
			wrong_args("Invalid file extension");
		if ((data->maps.fd = open(argv[1], O_RDONLY)) == -1)
			wrong_args("Couldn't open .cub file");
	}
}

int		main(int argc, char **argv)
{
	t_data data;

	check_args_errors(&data, argc, argv);
	parse_cub_file(&data);
	init_data(&data);
	hook_event(&data);
	mlx_loop_hook(data.mlx, render_next_ray, &data);
	mlx_loop(data.mlx);
	return (0);
}