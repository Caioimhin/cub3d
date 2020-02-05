/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:11:27 by kparis            #+#    #+#             */
/*   Updated: 2020/02/05 17:06:16 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../libft/libft.h"

typedef struct	s_img
{
	void		*img;
	void		*img_cpy;
	void		*adress;
	int			bits_per_pxl;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_map
{
	char	*res;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	char	*floor;
	char	*ceiling;
}				t_map;


typedef	struct	s_mlx {
	void		*mlx;
	void		*window;
	t_img		*img;
}				t_mlx;