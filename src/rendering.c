/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:31:36 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/07 12:19:29 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Custom pixel put function: writes color to (x, y) in image buffer
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
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
t_draw_context	create_draw_context(t_data *img, t_map *map, int line_color)
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
t_point2d	get_projected_point(int x, int y, int z, t_draw_context *ctx)
{
	t_point	point;

	point = (t_point){x * ctx->map->scale, y * ctx->map->scale, z};
	return (project_point(point, ctx->map, ctx->x_offset, ctx->y_offset));
}
