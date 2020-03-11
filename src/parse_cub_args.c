/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 10:51:51 by kparis            #+#    #+#             */
/*   Updated: 2020/03/11 11:31:00 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_cub_args(t_mlx *data)
{
	int fd;
	char line[100];

	if ((fd = open(data->map->cub_path, O_RDONLY)) == -1)
		error_message("Cannot open this file");
	read(fd, line, 100);
	ft_putendl(line);
	close(fd);
}
