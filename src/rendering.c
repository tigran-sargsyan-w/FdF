/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:31:36 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/15 16:55:08 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Custom pixel put function: writes color to (x, y) in image buffer
void	my_mlx_pixel_put(t_vars *vars, t_point2d point, int color)
{
	char	*dst;

	if (point.x >= 0 && point.x < vars->screen_width && point.y >= 0
		&& point.y < vars->screen_height)
	{
		dst = vars->data.addr + (point.y * vars->data.line_length + point.x
				* (vars->data.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

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

// Function to adjust scale of the map to fit the window
void	adjust_initial_scale(t_vars *vars)
{
	int		max_width;
	int		max_height;
	float	scale_x;
	float	scale_y;
	float	factor;

	factor = 0.8;
	max_width = vars->screen_width * factor;
	max_height = vars->screen_height * factor;
	scale_x = (float)max_width / vars->map->columns;
	scale_y = (float)max_height / vars->map->rows;
	vars->map->scale = fmin(scale_x, scale_y);
	vars->map->zoom_factor = 1.0;
}
