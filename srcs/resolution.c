/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:58:37 by kparis            #+#    #+#             */
/*   Updated: 2020/05/21 15:44:53 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_resolution(t_data *data, char *line, t_maps *maps)
{
	int x;

	x = 0;
	while (!ft_isdigit(line[x]))
		x++;
	maps->win_size.x = ft_atoi(&line[x]);
	while(ft_isdigit(line[x]))
		x++;
	while (line[x] == ' ')
		x++;
	maps->win_size.y = ft_atoi(&line[x]);
	while(ft_isdigit(line[x]))
		x++;
	while (line[x] == ' ')
		x++;
	// int	x;

	// x = 1;
	// maps->win_size.x = 0;
	// maps->win_size.y = 0;
	// while (line[x] == ' ')
	// 	x++;
	// while (ft_isdigit(line[x]))
	// 	maps->win_size.x = (maps->win_size.x * 10) + (line[x++] - '0');
	// while (line[x] == ' ')
	// 	x++;
	// while (ft_isdigit(line[x]))
	// 	maps->win_size.y = (maps->win_size.y * 10) + (line[x++] - '0');
	// while (line[x] == ' ')
	// 	x++;
	if (line[x])
		close_program(data, "Wrong resolution in .cub file\n", "");
	if (maps->win_size.x < 50 || maps->win_size.y < 50)
		close_program(data, "Resolution is too small\n", "");
	if (maps->win_size.x > 2560)
		maps->win_size.x = 2560;
	if (maps->win_size.y > 1440)
		maps->win_size.y = 1440;
}
