/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:31:36 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/05 13:31:49 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to compute isometric projection for a 3D point
t_point2d	iso_projection(t_point pt, double angle)
{
	t_point2d	proj;

	proj.x = (int)((pt.x - pt.y) * cos(angle));
	proj.y = (int)((pt.x + pt.y) * sin(angle) - pt.z);
	return (proj);
}

// Custom pixel put function: writes color to (x, y) in image buffer
static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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
static void	draw_line_loop(t_data *img, t_line line, t_line_params lp,
		int color)
{
	int			double_error;
	t_point2d	start;
	t_point2d	end;

	start = line.start;
	end = line.end;
	while (1)
	{
		my_mlx_pixel_put(img, start.x, start.y, color);
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
void	draw_line(t_data *img, t_point2d start, t_point2d end, int color)
{
	t_line_params	lp;
	t_line			line;

	line.start = start;
	line.end = end;
	lp = init_line_params(start, end);
	draw_line_loop(img, line, lp, color);
}
