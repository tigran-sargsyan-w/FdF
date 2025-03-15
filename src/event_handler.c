/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:33:39 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/15 13:17:13 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_projected_points(t_vars *vars)
{
	t_point	rotated;
	int		x_offset;
	int		y_offset;
	int		i;
	int		j;

	compute_bounding_box(vars);
	x_offset = ((vars->screen_width + MENU_WIDTH) - (vars->box.max_x
				- vars->box.min_x)) / 2 - vars->box.min_x;
	y_offset = (vars->screen_height - (vars->box.max_y - vars->box.min_y)) / 2
		- vars->box.min_y;
	i = 0;
	while (i < vars->map->rows)
	{
		j = 0;
		while (j < vars->map->columns)
		{
			rotated = (t_point){j * vars->map->scale, i * vars->map->scale,
				vars->map->values[i][j]};
			rotated = rotate_point(rotated, vars->map);
			rotated.x *= vars->map->zoom_factor;
			rotated.y *= vars->map->zoom_factor;
			rotated.z *= vars->map->zoom_factor;
			if (vars->map->projection_mode == ISO)
				vars->map->projected_points[i][j] = iso_projection(rotated,
						vars->map->flatten_factor);
			else if (vars->map->projection_mode == PARALLEL)
				vars->map->projected_points[i][j] = parallel_projection(rotated,
						vars->map->parallel_factor);
			else if (vars->map->projection_mode == ORTHO)
				vars->map->projected_points[i][j] = ortho_projection(rotated);
			else
				vars->map->projected_points[i][j] = iso_projection(rotated,
						vars->map->flatten_factor);
			vars->map->projected_points[i][j].x += x_offset
				+ vars->map->trans_x;
			vars->map->projected_points[i][j].y += y_offset
				+ vars->map->trans_y;
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
}

void	handle_flatten(t_vars *vars, int keycode)
{
	if (keycode == KEY_PAGE_UP)
		apply_flatten(vars->map, FLATTEN_DECREMENT);
	else if (keycode == KEY_PAGE_DOWN)
		apply_flatten(vars->map, FLATTEN_INCREMENT);
}

void	handle_rotation(t_vars *vars, int keycode)
{
	if (keycode == KEY_ARROW_UP)
		handle_rotation_left(vars, &vars->map->rot_x);
	else if (keycode == KEY_ARROW_DOWN)
		handle_rotation_right(vars, &vars->map->rot_x);
	else if (keycode == KEY_ARROW_LEFT)
		handle_rotation_left(vars, &vars->map->rot_y);
	else if (keycode == KEY_ARROW_RIGHT)
		handle_rotation_right(vars, &vars->map->rot_y);
	else if (keycode == KEY_Q)
		handle_rotation_left(vars, &vars->map->rot_z);
	else if (keycode == KEY_E)
		handle_rotation_right(vars, &vars->map->rot_z);
}

void	handle_rotation_left(t_vars *vars, float *axis)
{
	if (vars->shift_pressed)
		*axis -= 90;
	else
		*axis -= ROTATION_SPEED;
	if (*axis <= -360)
		*axis = 0;
}

void	handle_rotation_right(t_vars *vars, float *axis)
{
	if (vars->shift_pressed)
		*axis += 90;
	else
		*axis += ROTATION_SPEED;
	if (*axis >= 360)
		*axis = 0;
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
}

void	handle_projection_mode(t_vars *vars, int keycode)
{
	if (keycode == KEY_P)
	{
		if (vars->map->projection_mode == ISO)
			vars->map->projection_mode = ORTHO;
		else if (vars->map->projection_mode == ORTHO)
			vars->map->projection_mode = PARALLEL;
		else
			vars->map->projection_mode = ISO;
	}
}

void	handle_reset(t_vars *vars, int keycode)
{
	if (keycode == KEY_R)
	{
		vars->map->rot_x = 0;
		vars->map->rot_y = 0;
		vars->map->rot_z = 0;
		vars->map->projection_mode = ISO;
		vars->map->flatten_factor = 1.0;
		vars->map->zoom_factor = 1.0;
		vars->map->trans_x = 0;
		vars->map->trans_y = 0;
	}
}

void	handle_mouse_zoom(t_vars *vars, int button)
{
	if (button == MOUSE_SCROLL_UP)
		apply_zoom(vars->map, ZOOM_IN_FACTOR);
	else if (button == MOUSE_SCROLL_DOWN)
		apply_zoom(vars->map, ZOOM_OUT_FACTOR);
}

void	handle_exit(t_vars *vars, int keycode)
{
	if (keycode == KEY_ESC)
		cleanup_and_exit(vars);
}
