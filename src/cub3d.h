/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:11:27 by kparis            #+#    #+#             */
/*   Updated: 2020/03/11 11:22:45 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../miniLibX/mlx.h"

# define RES_X_MAX 2560
# define RES_Y_MAX 1440
# define RES_X_MIN 192
# define RES_Y_MIN 108
# define ESC 53
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define TURN_LEFT 123
# define TURN_RIGHT 124

typedef struct	s_map
{
	int		save;
	char	*cub_path;
}				t_map;

typedef struct	s_mlx
{
	t_map		*map;
}				t_mlx;

void	parse_cub_args(t_mlx *data);
void	error_message(char *text);
#endif
