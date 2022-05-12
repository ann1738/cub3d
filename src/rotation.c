/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ann <ann@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 00:31:35 by ann               #+#    #+#             */
/*   Updated: 2022/05/11 16:06:04 by ann              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_coor(double *x, double *y, double angle)
{
	double temp_x;

	temp_x = *x;
	*x = (*x * cos(angle)) - (*y * sin(angle));
	*y = (temp_x * sin(angle)) + (*y * cos(angle));
}
