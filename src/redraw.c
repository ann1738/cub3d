/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalsuwai <aalsuwai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:44:04 by anasr             #+#    #+#             */
/*   Updated: 2022/05/25 18:37:02 by aalsuwai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	show_info_panel(t_main *s)
{
	t_coord	temp;

	temp.x = 520;
	temp.y = 220;
	temp.color = HX_BLACK;
	draw_border(600, 450, &temp, s);
	make_rect_trans(600, 450, &temp, &s->minimap_color, s);
	mlx_put_image_to_window(s->mlx, s->mlx_window, s->mlx_image, 0, 0);
	mlx_string_put(s->mlx, s->mlx_window, 560, (220 + 50), 0x57d29d, \
	"How to play:"); // green
	// mlx_string_put(s->mlx, s->mlx_window, 550, (220 + 50), 0xFF6633, "How to play:"); // orange
	mlx_string_put(s->mlx, s->mlx_window, 620, (220 + (60 + 30)), \
	0xF9DB24, "        - Use W A S D keys to move."); // yellow
	mlx_string_put(s->mlx, s->mlx_window, 620, (220 + (60 + (30 * 3))), \
	0xF9DB24, "        - Use right and left arrows to turn.");
	mlx_string_put(s->mlx, s->mlx_window, 620, (220 + (60 + (30 * 5))), \
	0xF9DB24, "        - Use the H key to enable mouse rotation.");
	mlx_string_put(s->mlx, s->mlx_window, 620, (220 + (60 + (30 * 7))), \
	0xF9DB24, "        - Use the M key to show or remove the minimap.");
	mlx_string_put(s->mlx, s->mlx_window, 620, (220 + (60 + (30 * 9))), \
	0xF9DB24, "        - Use the I key to show or remove the info panel.");
	mlx_string_put(s->mlx, s->mlx_window, 620, (220 + (60 + (30 * 11))), \
	0xF9DB24, "        - Use the ESC key to exit the game.");
}

static void	put_leaf_count(t_main *s)
{
	char	*temp;

	mlx_put_image_to_window(s->mlx, s->mlx_window, s->leaf_dude[8].image, 440, 10);
	temp = ft_itoa(s->p->full_sprite_count);
	mlx_string_put(s->mlx, s->mlx_window, 480, 29, 0x394f51, temp);
	free(temp);
}

/* function to draw everything in the image and put into the window */
void	redraw_window(t_main *s)
{
	/* clear window */
	ft_bzero(s->image_address, s->size_line * WINDOW_Y);

	/* draw floor and ceiling */
	if (!s->p->f_is_texture)
		draw_floor(s->floor_color, &s->fog, s);
	else
		floor_n_ceiling_cast(s, &s->floor_tex, WINDOW_Y / 2);
	if (!s->p->c_is_texture)
		draw_ceiling(s->ceiling_color, &s->fog, s);
	else
		floor_n_ceiling_cast(s, &s->ceiling_tex, 0);
	/* cast rays */
	cast_rays(s);

	/* sprite */
	if (s->sprite->in_screen_count)
		sprite_cast(s, &s->leaf_dude[s->leaf_index]);

	/* minimap drawing */
	if (s->minimap_on)
		draw_minimap(s);

	/* putting the image to the window */
	mlx_put_image_to_window(s->mlx, s->mlx_window, s->mlx_image, 0, 0);

	/* info bar */
	if (s->info_panel_on)
		show_info_panel(s);

	/* leaf count */
	if (s->p->leaf_is_here)
		put_leaf_count(s);
	if (s->p->leaf_is_here && !s->p->full_sprite_count && ++s->end_screen_done)
		mlx_put_image_to_window(s->mlx, s->mlx_window, s->end_screen.image, 0, 0);
}
