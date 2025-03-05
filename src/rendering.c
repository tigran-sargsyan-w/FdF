/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:31:36 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/05 22:11:08 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to compute isometric projection for a 3D point
static t_point2d	iso_projection(t_point pt)
{
	t_point2d	proj;

	proj.x = (int)round((pt.x - pt.y) * cos(ISO_ANGLE));
	proj.y = (int)round((pt.x + pt.y) * sin(ISO_ANGLE) - (pt.z / Z_FACTOR));
	return (proj);
}

// Custom pixel put function: writes color to (x, y) in image buffer
static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
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

void	compute_bounding_box(t_map *map, t_bbox *box)
{
	int			i;
	int			j;
	t_point		current;
	t_point2d	proj;

	box->min_x = INT_MAX;
	box->max_x = INT_MIN;
	box->min_y = INT_MAX;
	box->max_y = INT_MIN;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->columns)
		{
			current.x = j * SCALE;
			current.y = i * SCALE;
			current.z = map->values[i][j];
			proj = iso_projection(current);
			if (proj.x < box->min_x)
				box->min_x = proj.x;
			if (proj.x > box->max_x)
				box->max_x = proj.x;
			if (proj.y < box->min_y)
				box->min_y = proj.y;
			if (proj.y > box->max_y)
				box->max_y = proj.y;
			j++;
		}
		i++;
	}
}

void	draw_grid(t_data *img, t_map *map, int line_color)
{
	int			i;
	int			j;
	int			img_width;
	int			img_height;
	int			x_offset;
	int			y_offset;
	t_bbox		box;
	t_point		current;
	t_point		next;
	t_point2d	proj_current;
	t_point2d	proj_next;

	compute_bounding_box(map, &box);
	img_width = box.max_x - box.min_x;
	img_height = box.max_y - box.min_y;
	x_offset = (WINDOW_WIDTH - img_width) / 2 - box.min_x;
	y_offset = (WINDOW_HEIGHT - img_height) / 2 - box.min_y;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->columns)
		{
			current.x = j * SCALE;
			current.y = i * SCALE;
			current.z = map->values[i][j];
			proj_current = iso_projection(current);
			proj_current.x += x_offset;
			proj_current.y += y_offset;
			// Если есть сосед справа, отрисовываем горизонтальную линию
			if (j < map->columns - 1)
			{
				next.x = (j + 1) * SCALE;
				next.y = i * SCALE;
				next.z = map->values[i][j + 1];
				proj_next = iso_projection(next);
				proj_next.x += x_offset;
				proj_next.y += y_offset;
				draw_line(img, proj_current, proj_next, line_color);
			}
			// Если существует сосед снизу, отрисовываем вертикальную линию
			if (i < map->rows - 1)
			{
				next.x = j * SCALE;
				next.y = (i + 1) * SCALE;
				next.z = map->values[i + 1][j];
				proj_next = iso_projection(next);
				proj_next.x += x_offset;
				proj_next.y += y_offset;
				draw_line(img, proj_current, proj_next, line_color);
			}
			j++;
		}
		i++;
	}
}
