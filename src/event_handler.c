/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:33:39 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/10 21:57:26 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_projected_points(t_map *map)
{
	t_bbox	box;
	t_point	rotated;
	int		x_offset;
	int		y_offset;
	int		i;
	int		j;

	compute_bounding_box(map, &box);
	x_offset = (WINDOW_WIDTH - (box.max_x - box.min_x)) / 2 - box.min_x;
	y_offset = (WINDOW_HEIGHT - (box.max_y - box.min_y)) / 2 - box.min_y;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->columns)
		{
			rotated = (t_point){j * map->scale, i * map->scale,
				map->values[i][j]};
			rotated = rotate_point(rotated, map);
			rotated.x *= map->zoom_factor;
			rotated.y *= map->zoom_factor;
			rotated.z *= map->zoom_factor;
			map->projected_points[i][j] = iso_projection(rotated);
			map->projected_points[i][j].x += x_offset + map->trans_x;
			map->projected_points[i][j].y += y_offset + map->trans_y;
			j++;
		}
		i++;
	}
}

void	handle_zoom(t_vars *vars, int keycode)
{
	if (keycode == KEY_NUM_PLUS)
		apply_zoom(vars->map, ZOOM_IN_FACTOR);
	else if (keycode == KEY_NUM_MINUS)
		apply_zoom(vars->map, ZOOM_OUT_FACTOR);
	update_projected_points(vars->map);
}

void	handle_rotation(t_vars *vars, int keycode)
{
	if (keycode == KEY_ARROW_UP)
		vars->map->rot_x -= ROTATION_SPEED;
	else if (keycode == KEY_ARROW_DOWN)
		vars->map->rot_x += ROTATION_SPEED;
	else if (keycode == KEY_ARROW_LEFT)
		vars->map->rot_y -= ROTATION_SPEED;
	else if (keycode == KEY_ARROW_RIGHT)
		vars->map->rot_y += ROTATION_SPEED;
	else if (keycode == KEY_Q)
		vars->map->rot_z -= ROTATION_SPEED;
	else if (keycode == KEY_E)
		vars->map->rot_z += ROTATION_SPEED;
	update_projected_points(vars->map);
}

void	handle_translation(t_vars *vars, int keycode)
{
	if (keycode == KEY_W)
		vars->map->trans_y -= MOVE_SPEED;
	else if (keycode == KEY_S)
		vars->map->trans_y += MOVE_SPEED;
	else if (keycode == KEY_A)
		vars->map->trans_x -= MOVE_SPEED;
	else if (keycode == KEY_D)
		vars->map->trans_x += MOVE_SPEED;
	update_projected_points(vars->map);
}

void	handle_exit(t_vars *vars, int keycode)
{
	if (keycode == KEY_ESC)
	{
		cleanup_and_exit(vars);
		exit(0);
	}
}
