/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:31:36 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/20 23:07:56 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Computes the projected point based on the map's projection mode and
 * the given offset.
 * @param map Structure of the map containing the projection mode and scale.
 * @param row_index Row index of the point.
 * @param column_index Column index of the point.
 * @param offset Offset to be applied to the projected point.
 */
static void	compute_projected_point(t_map *map, int row_index, int column_index,
		t_point2d offset)
{
	t_point	point;

	point = (t_point){column_index * map->scale, row_index * map->scale,
		map->values[row_index][column_index]};
	point = rotate_point(point, map);
	point.x *= map->zoom_factor;
	point.y *= map->zoom_factor;
	point.z *= map->zoom_factor;
	if (map->projection_mode == ISO)
		map->render_points[row_index][column_index] = to_isometric(point,
				map->flatten_factor);
	else if (map->projection_mode == PARALLEL)
		map->render_points[row_index][column_index] = to_parallel(point);
	else if (map->projection_mode == ORTHO)
		map->render_points[row_index][column_index] = to_orthographic(point);
	else
		map->render_points[row_index][column_index] = to_isometric(point,
				map->flatten_factor);
	map->render_points[row_index][column_index].x += offset.x + map->trans_x;
	map->render_points[row_index][column_index].y += offset.y + map->trans_y;
}

/**
 * @brief Draws the background of the window.
 * @param vars Structure containing main variables.
 */
static void	draw_background(t_vars *vars)
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
			draw_pixel(vars, pt, bg_color);
			pt.x++;
		}
		pt.y++;
	}
}

/**
 * @brief Updates the projected points of the map based on the current
 * projection mode and scale.
 * @param vars Structure containing main variables.
 */
static void	update_projected_points(t_vars *vars)
{
	t_point2d	offset;
	int			i;
	int			j;

	compute_bounding_box(vars);
	offset.x = ((vars->screen_width + MENU_WIDTH) - (vars->box.max_x
				- vars->box.min_x)) / 2 - vars->box.min_x;
	offset.y = (vars->screen_height - (vars->box.max_y - vars->box.min_y)) / 2
		- vars->box.min_y;
	i = 0;
	while (i < vars->map->rows)
	{
		j = 0;
		while (j < vars->map->columns)
		{
			compute_projected_point(vars->map, i, j, offset);
			j++;
		}
		i++;
	}
}

/**
 * @brief Draws a pixel on the image buffer at the specified coordinates.
 * @param vars Structure containing main variables.
 * @param point Coordinates of the pixel to be drawn.
 * @param color Color of the pixel.
 */
void	draw_pixel(t_vars *vars, t_point2d point, int color)
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

/**
 * @brief Updates the scene by redrawing the background, projected points,
 * grid, and menu.
 * @param vars Structure containing main variables.
 */
void	update_scene(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->data.img);
	vars->data.img = mlx_new_image(vars->mlx, vars->screen_width,
			vars->screen_height);
	vars->data.addr = mlx_get_data_addr(vars->data.img,
			&vars->data.bits_per_pixel, &vars->data.line_length,
			&vars->data.endian);
	draw_background(vars);
	update_projected_points(vars);
	draw_grid(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	draw_menu(vars);
}
