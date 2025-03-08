/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:33:39 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/08 14:01:13 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_zoom(t_vars *vars, int keycode)
{
	if (keycode == KEY_NUM_PLUS)
		apply_zoom(vars->map, ZOOM_IN_FACTOR);
	else if (keycode == KEY_NUM_MINUS)
		apply_zoom(vars->map, ZOOM_OUT_FACTOR);
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

void	handle_exit(t_vars *vars, int keycode)
{
	if (keycode == KEY_ESC)
	{
		cleanup_and_exit(vars);
		exit(0);
	}
}
