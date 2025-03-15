/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:03:19 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/15 15:43:08 by tsargsya         ###   ########.fr       */
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

// Draw line between two points with a specified color
static void	draw_line(t_vars *vars, t_point2d start, t_point2d end, int color)
{
	t_line_params	lp;
	int				double_error;

	lp = init_line_params(start, end);
	while (1)
	{
		my_mlx_pixel_put(vars, start, color);
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

static void	draw_horizontal_line(int i, int j, t_vars *vars, t_point2d current)
{
	t_point2d	next;

	if (j < vars->map->columns - 1)
	{
		next = vars->map->projected_points[i][j + 1];
		draw_line(vars, current, next, vars->map->colors[i][j]);
	}
}

static void	draw_vertical_line(int i, int j, t_vars *vars, t_point2d current)
{
	t_point2d	next;

	if (i < vars->map->rows - 1)
	{
		next = vars->map->projected_points[i + 1][j];
		draw_line(vars, current, next, vars->map->colors[i][j]);
	}
}

// Function to draw grid
void	draw_grid(t_vars *vars)
{
	int			i;
	int			j;
	t_point2d	point;

	i = 0;
	while (i < vars->map->rows)
	{
		j = 0;
		while (j < vars->map->columns)
		{
			point = vars->map->projected_points[i][j];
			draw_horizontal_line(i, j, vars, point);
			draw_vertical_line(i, j, vars, point);
			j++;
		}
		i++;
	}
}
