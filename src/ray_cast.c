/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 18:58:18 by ann               #+#    #+#             */
/*   Updated: 2022/05/13 18:46:09 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_ray_dir_n_delta_dist(t_main *s, double i)
{
	//calculate ray direction and initialize s->ray_map_position with the player map position
	s->ray_direction.x = cos(s->player_angle) + (s->camera_plane.x * i);
	s->ray_direction.y = sin(s->player_angle) + (s->camera_plane.y * i);
	// if (!i || i == -1.0 || i == 1.0)
	// 	printf("**********<%lf>************\n", rad_to_deg(atan2(s->ray_direction.y, s->ray_direction.x)));
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

static void	calc_inital_side_len(t_main *s)
{
	s->step.x = 0;
	s->step.y = 0;
	/* calculating the inital ray length to reach the side of the next wall in terms of x and y */
	if (s->ray_direction.x >= 0 && (++s->step.x) >= 0)
		s->side_length_x = ((s->ray_map_position.x + 1) - s->player_position.x) * s->delta_distance_x;
	else if ((--s->step.x) <= 0)
		s->side_length_x = (s->player_position.x - s->ray_map_position.x) * s->delta_distance_x;
	if (s->ray_direction.y >= 0 && ((++s->step.y) >= 0))
		s->side_length_y = ((s->ray_map_position.y + 1) - s->player_position.y) * s->delta_distance_y;
	else if ((--s->step.y) <= 0)
		s->side_length_y = (s->player_position.y - s->ray_map_position.y) * s->delta_distance_y;
	if (s->side_length_x < s->side_length_y)
		s->final_side_length = s->side_length_x;
	else
		s->final_side_length = s->side_length_y;
	// printf("step_x = %d, step_y = %d\n", s->step.x, s->step.y);
}
	// if (s->side_hit == SIDE_X)
	// 	origin.color = HX_BLUE;
	// else
	// 	origin.color = 0x86c5da;

# define HX_PURPLE_0 0x9932CC
# define HX_PURPLE_1 0x9400D3
# define HX_PURPLE_2 0x4B0082
// # define HX_PURPLE_3 0x9455f4


int	assign(unsigned int *assigned, unsigned int assignee)
{
	*assigned = assignee;
	return (0);
}

static void	draw_wall(t_main *s)
{
	t_coord	origin;

	//calculate the perpendicular wall distance (to avoid fisheye)
	// if (s->side_hit == SIDE_X)
	// 	s->perpend_wall_dist = s->side_length_x - s->delta_distance_x;
	// else
	// 	s->perpend_wall_dist = s->side_length_y - s->delta_distance_y;
	s->perpend_wall_dist = s->final_side_length * fabs(cos(fabs(s->player_angle - atan2(s->ray_direction.y, s->ray_direction.x))));
	if (s->perpend_wall_dist > s->depth)
		return ;
	if (s->perpend_wall_dist < 2.0)	
		s->wall_height = WINDOW_Y;
	else
		s->wall_height = WALL_SCALE_FACTOR * WINDOW_Y / s->perpend_wall_dist;
	
	printf("perpendicular-wall-distance: %lf -- wall height: %d\n", s->perpend_wall_dist, s->wall_height);
	
	/*I am working here*/
	if (s->side_hit == SIDE_X)
		s->wall_hit_pos = s->player_position.y + s->perpend_wall_dist * s->ray_direction.y;
	else
		s->wall_hit_pos = s->player_position.x + s->perpend_wall_dist * s->ray_direction.x;
	s->wall_hit_pos = s->wall_hit_pos - floor(s->wall_hit_pos);//to get the fraction

	s->offset = (int)(s->wall_hit_pos * s->texture[0].width);
	printf("hit pos: %lf\n", s->wall_hit_pos);
	s->texture_x = s->offset;
	//understand the math here please
	if (s->side_hit == SIDE_X && s->ray_direction.x > 0)
		s->texture_x = s->texture[0].width - s->texture_x - 1;
	else if (s->side_hit == SIDE_Y && s->ray_direction.y < 0)
		s->texture_x = s->texture[0].width - s->texture_x - 1;
	
	s->step_texture = s->texture[0].height / (double)s->wall_height;
	s->texture_y = 0;
	// s->wall_height = (ACTUAL_WALL_HEIGHT / s->perpend_wall_dist) * s->dist_to_projection_plane;
	// printf("height: %d*****************\n", s->wall_height);
	//calculate the start and the end of the vertical strip drawing
	
	// if (s->perpend_wall_dist <= s->depth / 4.0 && !assign(&origin.color, HX_PURPLE_0))
	// 	;
	// else if (s->perpend_wall_dist <= s->depth / 2.0 && !assign(&origin.color, HX_PURPLE_1))
	// 	;
	// else if (s->perpend_wall_dist <= s->depth / 2.0 && !assign(&origin.color, HX_PURPLE_2))
	// 	;
	// else if (s->perpend_wall_dist >= s->depth)
	// 	return ;
	origin.x = s->place_wall_at_x;
	origin.y = (WINDOW_Y / 2.0) - (s->wall_height / 2.0);
	// origin.color = HX_PURPLE;
	draw_vertical_texture(origin, s->wall_width, s->wall_height, &s->texture[0], s);
}

static void	ray_casting_loop(t_main *s)
{
	while (s->final_side_length <= s->depth && s->map[s->ray_map_position.y][s->ray_map_position.x] != '1')
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
		// printf("HULU!!!!\nfinal_side_length = %lf -- ", s->final_side_length);

		/* protection for when there is no wall / wall is too far */
		if (s->ray_map_position.y > s->map_height - 1 || s->ray_map_position.x > s->map_width_max - 1)
		{
			s->final_side_length = s->depth;
			break ;
		}
		// printf("I AM IN (%d, %d)\n", s->ray_map_position.x, s->ray_map_position.y);
	}
	if (s->final_side_length > s->depth)
		s->dont_draw = true;
		
}

void	cast_rays(t_main *s)
{
	double i;

	/* calculating fps */
	// fps(s);
	s->dont_draw = false;
	i = 1;
	s->place_wall_at_x = 0;
	s->wall_width = WINDOW_X / (2.0 / INCREMENT_RAY_CASTING) + 1;
	//WINDOW_X divided by the number of rays casted (plus one bec the condition of the loop is >= not >.. actually idk why?!)
	while (i >= -1)
	{
		/* calculations before the main ray casting loop */
		calc_ray_dir_n_delta_dist(s, i);
		calc_inital_side_len(s);
		// printf("START RAY (%d, %d)\n", s->ray_map_position.x, s->ray_map_position.y);

		/* main ray casting loop */
		ray_casting_loop(s);

		// printf("ray end(%d, %d)\n", s->ray_map_position.x, s->ray_map_position.y);
	
		/*drawing the wall*/
		// if (s->dont_draw == false)
			draw_wall(s);

		/* incrementing loop */
		i -= INCREMENT_RAY_CASTING;
		s->place_wall_at_x += s->wall_width;
	}
}

/* code for drawing lines to represent the rays casted */

	// //start point
	// temp_start.x = s->player_position.x * s->mini_width_unit; 
	// temp_start.y = s->player_position.y * s->mini_height_unit; 
	// //end point
	// // printf("final ray length %lf\n", s->final_side_length);
	// temp_end.x = temp_start.x + (s->final_side_length * s->mini_width_unit * cos(atan2(s->ray_direction.y, s->ray_direction.x)));
	// temp_end.y = temp_start.y + (s->final_side_length * s->mini_height_unit * sin(atan2(s->ray_direction.y, s->ray_direction.x)));
	// // printf("start(%d, %d), end(%d, %d)\n", temp_start.x, temp_start.y, temp_end.x, temp_end.y);
	// if (s->minimap_on && false == true)
	// 	draw_line(temp_start, temp_end, s);
		
/*******************************************************/

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