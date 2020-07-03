/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:58:37 by kparis            #+#    #+#             */
/*   Updated: 2020/07/04 00:10:51 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_res_values(t_data *data, t_maps *maps)
{
	int x;
	int y;

	mlx_get_screen_size(data->mlx, &x, &y);
	if (maps->win_size.x > x)
		maps->win_size.x = x;
	if (maps->win_size.y > y)
		maps->win_size.y = y;
}

void	get_resolution(t_data *data, char *line, t_maps *maps)
{
	int	i;

	i = 1;
	maps->win_size.x = -1;
	maps->win_size.y = -1;
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		maps->win_size.x = (maps->win_size.x * 10) + (line[i++] - '0');
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]))
		maps->win_size.y = (maps->win_size.y * 10) + (line[i++] - '0');
	while (line[i] == ' ')
		i++;
	if (line[i])
		close_program(data, "Wrong resolution in .cub file\n", "");
	if (maps->win_size.x < 50 || maps->win_size.y < 50)
		close_program(data, "Resolution is too small\n", "");
	if (maps->win_size.x == -1 || maps->win_size.y == -1)
		close_program(data, "Resolution is not set\n", "");
}
