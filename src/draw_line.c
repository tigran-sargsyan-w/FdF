/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:57:24 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/14 21:57:17 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Initialize line drawing parameters using Bresenham's algorithm
static t_line_params	init_line_params(t_point2d start, t_point2d end)
{
	t_line_params	lp;

	lp.delta_x = abs(end.x - start.x);
	lp.delta_y = -abs(end.y - start.y);
	if (start.x < end.x)
		lp.step_x = 1;
	else
		lp.step_x = -1;
	if (start.y < end.y)
		lp.step_y = 1;
	else
		lp.step_y = -1;
	lp.error = lp.delta_x + lp.delta_y;
	return (lp);
}

// Draw line loop using precomputed parameters and a specified color
static void	draw_line_loop(t_vars *vars, t_line line, t_line_params lp,
		int color)
{
	int			double_error;
	t_point2d	start;
	t_point2d	end;

	start = line.start;
	end = line.end;
	while (1)
	{
		my_mlx_pixel_put(vars, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		double_error = 2 * lp.error;
		if (double_error >= lp.delta_y)
		{
			lp.error += lp.delta_y;
			start.x += lp.step_x;
		}
		if (double_error <= lp.delta_x)
		{
			lp.error += lp.delta_x;
			start.y += lp.step_y;
		}
	}
}

// Draw line between two points with a specified color
void	draw_line(t_vars *vars, t_point2d start, t_point2d end, int color)
{
	t_line_params	lp;
	t_line			line;

	line.start = start;
	line.end = end;
	lp = init_line_params(start, end);
	draw_line_loop(vars, line, lp, color);
}
