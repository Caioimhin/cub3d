/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:31:57 by kparis            #+#    #+#             */
/*   Updated: 2020/01/16 13:42:00 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mlx.h"

int		close(void *param)
{
	(void)param;
	exit(0);
}

int main(void)
{

	typedef	struct s_mlx {
		void	*mlx;
		void	*window;
	}			t_mlx;

	t_mlx data;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, 2000, 1200, "Fucking AWESOME");
	mlx_string_put(data.mlx, data.window, 1000, 600, 199125, "Fucking AWESOME");
	mlx_hook(data.window, 17, 0, close, &data);
	system("leaks cub3d");
	mlx_loop(data.mlx);

	return (EXIT_SUCCESS);
}
