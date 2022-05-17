/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 14:33:14 by anasr             #+#    #+#             */
/*   Updated: 2022/05/17 06:01:28 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_uint(int transp, int red, int green, int blue)
{
	return (transp << 24 | red << 16 | green << 8 | blue);
}

void	uint_to_rgb(unsigned int uint_color, t_color *rgb_color)
{
	rgb_color->blue = (uint_color & 0x000000ff) & 255;
	rgb_color->green = ((uint_color & 0x0000ff00) >> 8) & 255;;
	rgb_color->red = ((uint_color & 0x00ff0000) >> 16) & 255;
	// printf("red is %d, green is %d, blue is %d\n", rgb_color->red, rgb_color->green, rgb_color->blue);
}

void	add_fog(double intensity, t_color fog_color, t_color *color)
{
	//account for overflow
	if (intensity >= 0 && intensity <= 1)
	{
		color->red = ((char)(color->red * (1.0 - intensity)) + (char)(fog_color.red * intensity)) & 255;
		color->green = ((char)(color->green * (1.0 - intensity)) + (char)(fog_color.green * intensity)) & 255;
		color->blue = ((char)(color->blue * (1.0 - intensity)) + (char)(fog_color.blue * intensity)) & 255;
	}
	else
		write(2, "Invalid intensity for the function add_fog\n", 43);
}

unsigned int	add_fog_uint(double intensity, t_color *fog_color, unsigned int color)
{
	int		r;
	int		g;
	int		b;
	double	intensity_inverse;

	intensity_inverse = 1.0 - intensity;
	r = ((char)((((color & 0x00ff0000) >> 16) & 255) * intensity_inverse) + (char)(fog_color->red * intensity)) & 255; // red
	g = ((char)((((color & 0x0000ff00) >> 8) & 255) * intensity_inverse) + (char)(fog_color->green * intensity)) & 255; // green
	b = ((char)((color & 0x000000ff) * intensity_inverse) + (char)(fog_color->blue * intensity)) & 255; // blue
	return (r << 16 | g << 8 | b);
}


void	assign_rgb_color(int red, int green, int blue, t_color *color)
{
	color->blue = blue & 255;
	color->green = green & 255;
	color->red = red & 255;
}