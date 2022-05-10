/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:58:18 by ann               #+#    #+#             */
/*   Updated: 2022/05/10 17:02:41 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// double	d_abs(double x)
// {
// 	if (x < 0)
// 		x *= -1;
// 	return (x);
// }

// s->ray_direction.x = s->player_direction.x + s->camera_plane.x;
// s->ray_direction.y = s->player_direction.y + s->camera_plane.y;

void	calc_ray_dir_n_delta_dist(t_main *s, double i)
{
	//calculate ray direction and initialize s->ray_map_position with the player map position
	s->ray_direction.x = cos(s->player_angle) + (s->camera_plane.x * i);
	s->ray_direction.y = sin(s->player_angle) + (s->camera_plane.y * i);
	s->ray_map_position.x = s->player_map_position.x;
	s->ray_map_position.y = s->player_map_position.y;
	//calculate delta distances *
	if (s->ray_direction.x != 0)
		s->delta_distance_x = sqrt(1 + (s->ray_direction.y / s->ray_direction.x) * (s->ray_direction.y / s->ray_direction.x));
	else
		s->delta_distance_x = 1e8;
	if (s->ray_direction.y != 0)
		s->delta_distance_y = sqrt(1 + (s->ray_direction.x / s->ray_direction.y) * (s->ray_direction.x / s->ray_direction.y));
	else
		s->delta_distance_y = 1e8;
}

void	calc_inital_side_len(t_main *s)
{
	// calculating the inital ray length to reach the side of the next wall in terms of x and y
	if (s->ray_direction.x >= 0)
	{
		s->step.x = 1;
		s->side_length_x = ((s->ray_map_position.x + 1) - s->player_position.x) * s->delta_distance_x;
	}
	else
	{
		s->step.x = -1;
		s->side_length_x = (s->player_position.x - s->ray_map_position.x) * s->delta_distance_x;
	}
	if (s->ray_direction.y >= 0)
	{
		s->step.y = 1;
		s->side_length_y = ((s->ray_map_position.y + 1) - s->player_position.y) * s->delta_distance_y;
	}
	else
	{
		s->step.y = -1;
		s->side_length_y = (s->player_position.y - s->ray_map_position.y) * s->delta_distance_y;
	}
	if (s->side_length_x < s->side_length_y)
		s->final_side_length = s->side_length_x;
	else
		s->final_side_length = s->side_length_y;
	// printf("step_x = %d, step_y = %d\n", s->step.x, s->step.y);
}

void	draw_wall(t_main *s)
{
	t_coord	origin;

	//calculate the perpendicular wall distance (to avoid fisheye)
	if (s->side_hit == SIDE_X)
		s->perpend_wall_dist = s->side_length_x - s->delta_distance_x;
	else
		s->perpend_wall_dist = s->side_length_y - s->delta_distance_y;
	s->wall_height = WINDOW_Y / s->perpend_wall_dist;
	// printf("height: %d*****************\n", s->wall_height);
	//calculate the start and the end of the vertical strip drawing
	origin.x = s->place_wall_at_x;
	origin.y = (WINDOW_Y / 2.0) - (s->wall_height / 2);
	if (s->side_hit == SIDE_X)
		origin.color = HX_BLUE;
	else
		origin.color = 0x86c5da;
	draw_vertical_strip(origin, s->wall_width, s->wall_height, s);
}

void	cast_rays(t_main *s)
{
	t_coord	temp_start;
	t_coord	temp_end;
	double i;

	i = -1;
	s->place_wall_at_x = 0;
	s->wall_width = WINDOW_X / (2.0 / INCREMENT_RAY_CASTING) + 1; //WINDOW_X divided by the number of rays casted (plus one bec the condition of the loop is >= not >.. actually idk why?!)
	while (i <= 1)
	{
		calc_ray_dir_n_delta_dist(s, i);
		calc_inital_side_len(s);
		// printf("START RAY (%d, %d)\n", s->ray_map_position.x, s->ray_map_position.y);
		while (s->map[s->ray_map_position.y][s->ray_map_position.x] != '1')
		{
			// printf("I AM IN side.x = %lf , side.y = %lf\n", s->side_length_x, s->side_length_y);
			if (s->side_length_x < s->side_length_y)
			{
				s->final_side_length = s->side_length_x;
				s->side_length_x += s->delta_distance_x;
				s->ray_map_position.x += s->step.x;
				s->side_hit = SIDE_X;
			}
			else
			{
				s->final_side_length = s->side_length_y;
				s->side_length_y += s->delta_distance_y;
				s->ray_map_position.y += s->step.y;
				s->side_hit = SIDE_Y;
			}
			// printf("HULU!!!!\nfinal_side_length = %lf\n", s->final_side_length);
			// if (s->side_hit == SIDE_Y && ((s->final_side_length - s->delta_distance_y) > 6.0 || s->final_side_length < 0.05))
			// 	break ;
			// else if (s->side_hit == SIDE_X && ((s->final_side_length - s->delta_distance_x) > 6 || s->final_side_length < 0.05))
			// 	break ;
			// printf("I AM IN (%d, %d)\n", s->ray_map_position.x, s->ray_map_position.y);
		}
		// printf("ray end(%d, %d)\n", s->ray_map_position.x, s->ray_map_position.y);
		draw_wall(s);
		//start point
		temp_start.x = s->player_position.x * s->mini_width_unit; 
		temp_start.y = s->player_position.y * s->mini_height_unit; 
		//end point
		// printf("final ray length %lf\n", s->final_side_length);
		temp_end.x = temp_start.x + (s->final_side_length * s->mini_width_unit * cos(atan2(s->ray_direction.y, s->ray_direction.x)));
		temp_end.y = temp_start.y + (s->final_side_length * s->mini_height_unit * sin(atan2(s->ray_direction.y, s->ray_direction.x)));
		// printf("start(%d, %d), end(%d, %d)\n", temp_start.x, temp_start.y, temp_end.x, temp_end.y);
		if (s->minimap_on)
			draw_line(temp_start, temp_end, s);
		i += INCREMENT_RAY_CASTING;
		s->place_wall_at_x += s->wall_width;
	}
}

/* ************************************************************************** */
/* The goal is to cast a ray until hits a wall and use the distance to draw a */
/* vertical strip of the wall.                                                */
/* -------------------------------------------------------------------------- */
/* To do that:                                                                */
/* 1. calculate the length of the ray to traverse one x unit and also one y   */
/* unit. We'll call them s->delta_distance_x and s->delta_distance_y.         */
/* 2. calculate the inital hit to the next side wall in terms of hitting an x */
/* side or a y side.                                                          */
/* 3. use that */
/* ************************************************************************** */
