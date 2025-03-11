/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:44:13 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/11 21:47:31 by tsargsya         ###   ########.fr       */
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
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (x < MENU_WIDTH)
				bg_color = MENU_BG_COLOR;
			else
				bg_color = BG_COLOR;
			my_mlx_pixel_put(&vars->img, x, y, bg_color);
			x++;
		}
		y++;
	}
}
