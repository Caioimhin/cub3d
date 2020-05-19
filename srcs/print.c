/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kparis <kparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 18:58:25 by kparis            #+#    #+#             */
/*   Updated: 2020/05/19 17:40:51 by kparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_image(t_data *data)
{
	printf("\n         bpp = >%d<", data->img.bpp);
	printf("\n line length = >%d<", data->img.line_length);
	printf("\n      endian = >%d<", data->img.endian);
	printf("\nimage height = >%.d<", data->img.size.y);
	printf("\n image width = >%.d<", data->img.size.x);
	printf("\n colors[     0] = >%d<", data->img.colors[0]);
	printf("\n colors[ 50000] = >%d<", data->img.colors[50000]);
	printf("\n colors[100000] = >%d<", data->img.colors[100000]);
	printf("\n colors[150000] = >%d<", data->img.colors[150000]);
	printf("\n colors[200000] = >%d<", data->img.colors[200000]);
	printf("\n-------------------");
}

void	print_settings(t_data *data)//outil de verification a supprimer
{
	printf("\n-- maps --");
	printf("\nwin_size.x = %.d", data->maps.win_size.x);
	printf("\nwin_size.y = %.d", data->maps.win_size.y);
	printf("\nno_text_path = %s", data->maps.no_path);
	printf("\nso_text_path = %s", data->maps.so_path);
	printf("\nwe_text_path = %s", data->maps.we_path);
	printf("\nea_text_path = %s", data->maps.ea_path);
	printf("\nSprite_text_path = %s", data->maps.s_path);
	printf("\nFloor color = %d", data->maps.floor_color);
	printf("\nCeiling color = %d", data->maps.ceiling_color);
	printf("\nMap_width = %.d", data->maps.map_size.x);
	printf("\nMap_height = %.d", data->maps.map_size.y);
	printf("\nNumber of sprites = %d", data->maps.spr_count);
	printf("\nPlayer started at (%.d,%d)", data->maps.starting_pos.x, data->maps.starting_pos.y);
	printf("\nPlayer orientation = >%c<", data->maps.player_orientation);
/*
	int i = 0;
	int j = 0;
while (i < data->maps.map_size.y)
	{
		j = 0;
		if (i <= 9)
			printf("\nmap [ %d] : >", i);
		else
			printf("\nmap [%d] : >", i);
		while (j < (int)ft_strlen(data->maps.map[i]))
		{
			printf("%c ", data->maps.map[i][j]);
			j++;
		}
		i++;
		printf("<");
	}
	*/
	printf("\n\n");
}

void	print_situation(t_data* data)
{
	printf("\n\n  -- CURRENT SITUATION --\n--------------------");
	printf("\nplayer is located at (%.1f;%.1f)", data->ray.pos.x, data->ray.pos.y);
	printf("\ndir.x = %.2f", data->ray.dir.x);
	printf("\ndir.y = %.2f", data->ray.dir.y);
	printf("\ncamera plane.x = %.2f", data->ray.plane.x);
	printf("\ncamera plane.y = %.2f", data->ray.plane.y);
}

void	print_z_buffer(t_data *data)
{
	int i = 0;

	while (i < (int)data->maps.win_size.x)
	{
		if (i % 10 == 0)
		printf("%f ", data->ray.z_buffer[i]);
		if (i % 50 == 0)
		printf("\n");
		i++;
	}
}

void	print_ray(t_data* data)
{
	printf("\n-- RAY --");
	printf("\ncameraX = %.2f", data->ray.camera_x);
	printf("\nray.x = %.2f", data->ray.ray.x);
	printf("\nray.y = %.2f", data->ray.ray.y);
	printf("\nstep.x = %.d", data->ray.step.x);
	printf("\nstep.y = %.d", data->ray.step.y);
	printf("\ndelta_dist.x = %.2f", data->ray.delta_dist.x);
	printf("\ndelta_dist.y = %.2f", data->ray.delta_dist.y);
	printf("\nside_dist.x = %.2f", data->ray.side_dist.x);
	printf("\nside_dist.y = %.2f", data->ray.side_dist.y);
	printf("\n(map.x;map.y) = (%.2f, %.2f)", data->ray.map.x, data->ray.map.y);
	printf("\n(map.x;map.y) value = %c (char)", data->maps.map[(int)data->ray.map.y][(int)data->ray.map.x]);
	printf("\nside = %d", data->ray.side);
	printf("\nperp_wall_dist = %.2f", data->ray.perp_wall_dist);
	printf("\nline_height = %d", data->ray.line_height);
	printf("\ndraw_start = %d", data->ray.draw_start);
	printf("\ndraw_end = %d", data->ray.draw_end);
}
void	print_current_sprite_data(t_data *data)
{
	t_ray *F;

	F = &data->ray;
	printf("\nF->text.x = %d", F->text.x);
	printf("\nF->text.y = %d", F->text.y);
	printf("\nF->spr_inv.x = %.2f", F->spr_inv.x);
	printf("\nF->spr_inv.y = %.2f", F->spr_inv.y);
	printf("\nF->spr_size.x = %d", F->spr_size.x);
	printf("\nF->spr_size.y = %d", F->spr_size.y);
	printf("\nF->spr_draw_start.x = %d", F->spr_draw_start.x);
	printf("\nF->spr_draw_start.y = %d", F->spr_draw_start.y);
	printf("\nF->spr_draw_end.x = %d", F->spr_draw_end.x);
	printf("\nF->spr_draw_end.y = %d", F->spr_draw_end.y);
	printf("\nF->spr_screen_x = %.2f", F->spr_screen_x);

}

void	print_sprite_list(t_data *data)
{
	int	i = 0;
	int j = 0;

	ft_putstr_fd("\n  -- SPRITES --\n-----------------", 1);
	while(i < data->maps.spr_count || j < data->maps.spr_count)
	{
		if (j == data->ray.spr_order[i])
		{
			printf("\norder %d/sprite[%d] = (%.1f, %.1f/ text %c)", j, i,
					data->maps.spr_x[i],
					data->maps.spr_y[i],
					data->maps.spr_text[i]);
			printf("\nsprdist[%d]= >%.2f<", i, data->ray.spr_dist[i]);
			/*
			printf("\nspriteX = >%.1f<", data->ray.spriteX);
			printf("\nspriteY = >%.1f<", data->ray.spriteY);
			   printf("\ninvDet = >%f<", data->ray.invDet);
			   printf("\ntransfX = >%f<", data->ray.transfX);
			   printf("\ntransfY = >%f<", data->ray.transfY);
			   printf("\nspriteScreenX = >%d<", data->ray.spriteScreenX);
			   printf("\nspriteHeight = >%d<", data->ray.spriteHeight);
			   printf("\nspriteWidth = >%d<", data->ray.spriteWidth);
			   printf("\ndraw_startX = >%d<", data->ray.draw_startX);
			   printf("\ndraw_endX = >%d<", data->ray.draw_endX);
			   printf("\ndraw_startY = >%d<", data->ray.draw_startY);
			   printf("\ndraw_endY = >%d<", data->ray.draw_endY);
			   */
			j++;
			i = - 1;
		}
		i++;
	}
	printf("\n");
}


void	print_map(t_data *data)
{
	int i = - 1;
	int j = 0;

	while (i < data->maps.map_size.y)
	{
		j = 0;
		if (i == -1)
		{
			printf("\n             ");
			while (j < data->maps.map_size.x)
			{
				if (j < 10)
					printf("%d ", j);
				else if (j % 10 == 0)
					printf("%d", j);
				else
					printf(" %d", j%10);
				j++;
			}
			i++;
			j = 0;
		}
		if (i <= 9)
			printf("\nmap [ %d] : > ", i);
		else
			printf("\nmap [%d] : > ", i);
		while (j < (int)ft_strlen(data->maps.map[i]))
		{
			if (i == (int)data->ray.pos.y && j == (int)data->ray.pos.x)
			{
				if (data->ray.dir.y <= 0 && (fabs(data->ray.dir.y) > fabs(data->ray.dir.x)))
					printf("P^");
				else if (data->ray.dir.x >= 0  && (data->ray.dir.x > fabs(data->ray.dir.y)))
					printf("P>");
				else if (data->ray.dir.y >= 0  && (data->ray.dir.y > fabs(data->ray.dir.x)))
					printf("Pv");
				else if (data->ray.dir.x <= 0  && (fabs(data->ray.dir.x) > fabs(data->ray.dir.y)))
					printf("<P");
				else
					printf("ERROR");
			}
//			else if (i == (int)data->ray.first_map.y && j == (int)data->ray.first_map.x)
//				printf("r%c", data->maps.map[i][j]);
			else if (i == (int)data->ray.map.y && j == (int)data->ray.map.x)
				printf("R%c", data->maps.map[i][j]);
			else if (data->maps.map[i][j] == '0')
				printf("  ");
			else if (data->maps.map[i][j] == '1')
				printf("[]");
			else if (data->maps.map[i][j] == '2')
				printf("* ");
			else
				printf("%c ", data->maps.map[i][j]);
			j++;
		}
		i++;
		printf("<");
	}
	printf("\n");
}
