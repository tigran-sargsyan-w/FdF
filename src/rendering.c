/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:31:36 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/06 21:17:53 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Function to transfer degrees to radians
float	deg_to_rad(float angle)
{
	return (angle * M_PI / 180.0);
}

// Function to compute isometric projection for a 3D point
static t_point2d	iso_projection(t_point pt)
{
	t_point2d	proj;
	float		iso_angle;

	iso_angle = deg_to_rad(30);
	proj.x = (int)round((pt.x - pt.y) * cos(iso_angle));
	proj.y = (int)round((pt.x + pt.y) * sin(iso_angle) - (pt.z / Z_FACTOR));
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
static void	draw_line(t_data *img, t_point2d start, t_point2d end, int color)
{
	t_line_params	lp;
	t_line			line;

	line.start = start;
	line.end = end;
	lp = init_line_params(start, end);
	draw_line_loop(img, line, lp, color);
}

// Function to create border box for the map
static void	init_bbox(t_bbox *box)
{
	box->min_x = INT_MAX;
	box->max_x = INT_MIN;
	box->min_y = INT_MAX;
	box->max_y = INT_MIN;
}

// Function to update bounding box with a new point
static void	update_bbox(t_bbox *box, t_point2d proj)
{
	if (proj.x < box->min_x)
		box->min_x = proj.x;
	if (proj.x > box->max_x)
		box->max_x = proj.x;
	if (proj.y < box->min_y)
		box->min_y = proj.y;
	if (proj.y > box->max_y)
		box->max_y = proj.y;
}

// Function to compute bounding box for the map
static void	compute_bounding_box(t_map *map, t_bbox *box)
{
	int			i;
	int			j;
	t_point		current;
	t_point2d	proj;

	i = 0;
	init_bbox(box);
	while (i < map->rows)
	{
		j = 0;
		while (j < map->columns)
		{
			current = (t_point){j * map->scale, i * map->scale,
				map->values[i][j]};
			proj = iso_projection(current);
			update_bbox(box, proj);
			j++;
		}
		i++;
	}
}

// Function to adjust scale of the map to fit the window
void	adjust_scale(t_map *map)
{
	int		max_width;
	int		max_height;
	float	scale_x;
	float	scale_y;
	float	factor;

	factor = 0.5;
	max_width = WINDOW_WIDTH * factor;
	max_height = WINDOW_HEIGHT * factor;
	scale_x = (float)max_width / map->columns;
	scale_y = (float)max_height / map->rows;
	map->scale = fmin(scale_x, scale_y);
	map->zoom_factor = 1.0;
}

// Function to create draw context for the grid
static t_draw_context	create_draw_context(t_data *img, t_map *map,
		int line_color)
{
	t_draw_context	ctx;
	t_bbox			box;
	int				img_width;
	int				img_height;

	compute_bounding_box(map, &box);
	img_width = box.max_x - box.min_x;
	img_height = box.max_y - box.min_y;
	ctx.x_offset = (WINDOW_WIDTH - img_width) / 2 - box.min_x;
	ctx.y_offset = (WINDOW_HEIGHT - img_height) / 2 - box.min_y;
	ctx.img = img;
	ctx.map = map;
	ctx.line_color = line_color;
	return (ctx);
}

// Function to translate 2D point after projection
static t_point2d	translate_point(t_point2d p, t_map *map)
{
	p.x += map->trans_x;
	p.y += map->trans_y;
	return (p);
}

// Function to project a 3D point with an offset
static t_point2d	project_point(t_point point, t_map *map, int x_offset,
		int y_offset)
{
	t_point		rotated;
	t_point2d	projected;

	rotated = rotate_point(point, map);
	rotated.x *= map->zoom_factor;
	rotated.y *= map->zoom_factor;
	rotated.z *= map->zoom_factor;
	projected = iso_projection(rotated);
	projected.x += x_offset;
	projected.y += y_offset;
	return (translate_point(projected, map));
}

// Function to get projected point
static t_point2d	get_projected_point(int x, int y, int z,
		t_draw_context *ctx)
{
	t_point	point;

	point = (t_point){x * ctx->map->scale, y * ctx->map->scale, z};
	return (project_point(point, ctx->map, ctx->x_offset, ctx->y_offset));
}

// Function to draw a horizontal line
static void	draw_horizontal_line(int i, int j, t_draw_context *ctx,
		t_point2d proj_current)
{
	t_point2d	proj_next;

	if (j < ctx->map->columns - 1)
	{
		proj_next = get_projected_point(j + 1, i, ctx->map->values[i][j + 1],
				ctx);
		draw_line(ctx->img, proj_current, proj_next, ctx->line_color);
	}
}

// Function to draw a vertical line
static void	draw_vertical_line(int i, int j, t_draw_context *ctx,
		t_point2d proj_current)
{
	t_point2d	proj_next;

	if (i < ctx->map->rows - 1)
	{
		proj_next = get_projected_point(j, i + 1, ctx->map->values[i + 1][j],
				ctx);
		draw_line(ctx->img, proj_current, proj_next, ctx->line_color);
	}
}

// Function to draw cell lines
static void	draw_cell_lines(int i, int j, t_draw_context *ctx)
{
	t_point2d	proj_current;

	proj_current = get_projected_point(j, i, ctx->map->values[i][j], ctx);
	draw_horizontal_line(i, j, ctx, proj_current);
	draw_vertical_line(i, j, ctx, proj_current);
}

// Function to draw grid
void	draw_grid(t_vars vars, int line_color)
{
	t_draw_context	ctx;
	int				i;
	int				j;

	ctx = create_draw_context(&vars.img, vars.map, line_color);
	i = 0;
	while (i < vars.map->rows)
	{
		j = 0;
		while (j < vars.map->columns)
		{
			draw_cell_lines(i, j, &ctx);
			j++;
		}
		i++;
	}
}
