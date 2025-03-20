/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:03:19 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/20 12:57:33 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Initialize line drawing parameters using Bresenham's algorithm
static t_line_params	init_line_params(t_point2d start, t_point2d end)
{
	t_line_params	params;

	params.delta_x = abs(end.x - start.x);
	params.delta_y = -abs(end.y - start.y);
	if (start.x < end.x)
		params.step_x = 1;
	else
		params.step_x = -1;
	if (start.y < end.y)
		params.step_y = 1;
	else
		params.step_y = -1;
	params.error = params.delta_x + params.delta_y;
	return (params);
}

// Draw line between two points with a specified color
static void	draw_line(t_vars *vars, t_point2d start, t_point2d end, int color)
{
	t_line_params	line_params;
	int				double_error;

	line_params = init_line_params(start, end);
	while (1)
	{
		draw_pixel(vars, start, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		double_error = 2 * line_params.error;
		if (double_error >= line_params.delta_y)
		{
			line_params.error += line_params.delta_y;
			start.x += line_params.step_x;
		}
		if (double_error <= line_params.delta_x)
		{
			line_params.error += line_params.delta_x;
			start.y += line_params.step_y;
		}
	}
}

static void	draw_horizontal_line(int i, int j, t_vars *vars, t_point2d current)
{
	t_point2d	next;

	if (j < vars->map->columns - 1)
	{
		next = vars->map->render_points[i][j + 1];
		draw_line(vars, current, next, vars->map->colors[i][j]);
	}
}

static void	draw_vertical_line(int i, int j, t_vars *vars, t_point2d current)
{
	t_point2d	next;

	if (i < vars->map->rows - 1)
	{
		next = vars->map->render_points[i + 1][j];
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
			point = vars->map->render_points[i][j];
			draw_horizontal_line(i, j, vars, point);
			draw_vertical_line(i, j, vars, point);
			j++;
		}
		i++;
	}
}
