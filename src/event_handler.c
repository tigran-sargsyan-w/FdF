/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:33:39 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/12 20:29:00 by tsargsya         ###   ########.fr       */
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
			if (map->projection_mode == PROJ_ISO)
				map->projected_points[i][j] = iso_projection(rotated,
						map->flatten_factor);
			else if (map->projection_mode == PROJ_PARALLEL)
				map->projected_points[i][j] = parallel_projection(rotated,
						map->parallel_factor);
			else if (map->projection_mode == PROJ_ORTHO)
				map->projected_points[i][j] = ortho_projection(rotated, map);
			else
				map->projected_points[i][j] = iso_projection(rotated,
						map->flatten_factor);
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

void	handle_flatten(t_vars *vars, int keycode)
{
	if (keycode == KEY_PAGE_UP)
		apply_flatten(vars->map, FLATTEN_DECREMENT);
	else if (keycode == KEY_PAGE_DOWN)
		apply_flatten(vars->map, FLATTEN_INCREMENT);
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

void	handle_projection_mode(t_vars *vars, int keycode)
{
	if (keycode == KEY_P)
	{
		if (vars->map->projection_mode == PROJ_ISO)
		{
			vars->map->projection_mode = PROJ_ORTHO;
			printf("Switch projection mode to ORTHO\n");
		}
		else if (vars->map->projection_mode == PROJ_ORTHO)
		{
			vars->map->projection_mode = PROJ_PARALLEL;
			printf("Switch projection mode to PARALLEL\n");
		}
		else
		{
			vars->map->projection_mode = PROJ_ISO;
			printf("Switch projection mode to ISO\n");
		}
	}
	update_projected_points(vars->map);
}

void	handle_reset(t_vars *vars, int keycode)
{
	if (keycode == KEY_R)
	{
		vars->map->rot_x = 0;
		vars->map->rot_y = 0;
		vars->map->rot_z = 0;
		vars->map->projection_mode = PROJ_ISO;
		vars->map->flatten_factor = 1.0;
		vars->map->zoom_factor = 1.0;
		vars->map->trans_x = 0;
		vars->map->trans_y = 0;
		update_projected_points(vars->map);
	}
}

void	handle_exit(t_vars *vars, int keycode)
{
	if (keycode == KEY_ESC)
	{
		cleanup_and_exit(vars);
		exit(0);
	}
}
