/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:02:17 by anasr             #+#    #+#             */
/*   Updated: 2022/05/26 14:29:56 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	toggle_minimap_n_draw(t_main *s)
{
	s->minimap_on = !s->minimap_on;
	redraw_window(s);
}

void	toggle_mouse(t_main *s)
{
	s->is_using_mouse = !s->is_using_mouse;
	if (s->is_using_mouse)
		mlx_mouse_hide();
	else
		mlx_mouse_show();
}

void	toggle_info_n_draw(t_main *s)
{
	s->info_panel_on = !s->info_panel_on;
	redraw_window(s);
}
