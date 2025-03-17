/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:31:36 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/17 15:15:07 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	compute_projected_point(t_map *map, int i, int j, t_point2d offset)
{
	t_point	point;

	point = (t_point){j * map->scale, i * map->scale, map->values[i][j]};
	point = rotate_point(point, map);
	point.x *= map->zoom_factor;
	point.y *= map->zoom_factor;
	point.z *= map->zoom_factor;
	if (map->projection_mode == ISO)
		map->render_points[i][j] = to_isometric(point, map->flatten_factor);
	else if (map->projection_mode == PARALLEL)
		map->render_points[i][j] = to_parallel(point);
	else if (map->projection_mode == ORTHO)
		map->render_points[i][j] = to_orthographic(point);
	else
		map->render_points[i][j] = to_isometric(point, map->flatten_factor);
	map->render_points[i][j].x += offset.x + map->trans_x;
	map->render_points[i][j].y += offset.y + map->trans_y;
}

// Custom pixel put function: writes color to (x, y) in image buffer
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

void	update_scene(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->data.img);
	vars->data.img = mlx_new_image(vars->mlx, vars->screen_width,
			vars->screen_height);
	vars->data.addr = mlx_get_data_addr(vars->data.img,
			&vars->data.bits_per_pixel,
			&vars->data.line_length,
			&vars->data.endian);
	draw_background(vars);
	update_projected_points(vars);
	draw_grid(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
	draw_menu(vars);
}
