/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasr <anasr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:38:24 by anasr             #+#    #+#             */
/*   Updated: 2022/05/13 17:22:08 by anasr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(unsigned int color, t_main *s)
{
	t_coord	temp;

	temp.x = 0;
	temp.y = 0;
	temp.color = color;
	draw_rect(WINDOW_X, WINDOW_Y / 2, &temp, s);
}
