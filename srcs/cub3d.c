/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:57:06 by kparis            #+#    #+#             */
/*   Updated: 2020/05/19 16:10:32 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_args_errors(t_data *data, int argc, char **argv)
{
	if (argc == 1 || argc > 3)
		close_program(data, "Invalid number of arguments\n", "");
	if (argc == 3 && ft_memcmp(argv[1], "--save", 6))
		close_program(data, "Second argument is not --save\n", "");
	else if (argc == 3)
		data->save = 1;
	else
		data->save = 0;
	if (argc == 3)
	{
		if (ft_memcmp(&argv[2][ft_strlen(argv[2]) - 4], ".cub", 4))
			close_program(data, "File extension is not .cub\n", "");
		if ((data->maps.fd = open(argv[2], O_RDONLY)) == -1)
			close_program(data, "Couldn't open .cub file\n", "");
	}
	else
	{
		if (ft_memcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4))
			close_program(data, "File extension is not .cub\n", "");
		if ((data->maps.fd = open(argv[1], O_RDONLY)) == -1)
			close_program(data, "Couldn't open .cub file\n", "");
	}
}

int		main(int argc, char **argv)
{
	t_data data;

	check_args_errors(&data, argc, argv);
	parse_cub_file(&data);
	init_data(&data);
	hook_event(&data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
