/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:44:13 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/14 22:48:27 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_background(t_vars *vars)
{
	int	x;
	int	y;
	int	bg_color;

	bg_color = BG_COLOR;
	y = 0;
	while (y < vars->screen_height)
	{
		x = 0;
		while (x < vars->screen_width)
		{
			if (x < MENU_WIDTH)
				bg_color = MENU_BG_COLOR;
			else
				bg_color = BG_COLOR;
			my_mlx_pixel_put(vars, x, y, bg_color);
			x++;
		}
		y++;
	}
}
