/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:44:13 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/15 12:58:08 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_background(t_vars *vars)
{
	t_point2d	pt;
	int			bg_color;

	bg_color = BG_COLOR;
	pt.y = 0;
	while (pt.y < vars->screen_height)
	{
		pt.x = 0;
		while (pt.x < vars->screen_width)
		{
			if (pt.x < MENU_WIDTH)
				bg_color = MENU_BG_COLOR;
			else
				bg_color = BG_COLOR;
			my_mlx_pixel_put(vars, pt, bg_color);
			pt.x++;
		}
		pt.y++;
	}
}
