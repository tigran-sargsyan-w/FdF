/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_transform.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:49:55 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/21 11:28:28 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_rotation_left(t_vars *vars, float *axis);
static void	handle_rotation_right(t_vars *vars, float *axis);

/**
 * @brief Handles the rotation of the map to the left.
 * @brief Shifting the rotation by 90 degrees or rotating by a small amount.
 * @param vars Structure containing main variables.
 * @param axis Axis of rotation.
 */
static void	handle_rotation_left(t_vars *vars, float *axis)
{
	if (vars->shift_pressed)
		*axis -= 90;
	else
		*axis -= ROTATION_SPEED;
	if (*axis <= -360)
		*axis = 0;
}

/**
 * @brief Handles the rotation of the map to the right.
 * @brief Shifting the rotation by 90 degrees or rotating by a small amount.
 * @param vars Structure containing main variables.
 * @param axis Axis of rotation.
 */
static void	handle_rotation_right(t_vars *vars, float *axis)
{
	if (vars->shift_pressed)
		*axis += 90;
	else
		*axis += ROTATION_SPEED;
	if (*axis >= 360)
		*axis = 0;
}

/**
 * @brief Handles the translation of the map.
 * @param vars Structure containing main variables.
 * @param keycode Pressed key code.
 */
void	handle_translation(t_vars *vars, int keycode)
{
	if (keycode == XK_w)
		vars->map->trans_y -= MOVE_SPEED;
	else if (keycode == XK_s)
		vars->map->trans_y += MOVE_SPEED;
	else if (keycode == XK_a)
		vars->map->trans_x -= MOVE_SPEED;
	else if (keycode == XK_d)
		vars->map->trans_x += MOVE_SPEED;
}

/**
 * @brief Handles the rotation of the map.
 * @param vars Structure containing main variables.
 * @param keycode Pressed key code.
 */
void	handle_rotation(t_vars *vars, int keycode)
{
	if (keycode == XK_Up)
		handle_rotation_left(vars, &vars->map->rot_x);
	else if (keycode == XK_Down)
		handle_rotation_right(vars, &vars->map->rot_x);
	else if (keycode == XK_Left)
		handle_rotation_left(vars, &vars->map->rot_y);
	else if (keycode == XK_Right)
		handle_rotation_right(vars, &vars->map->rot_y);
	else if (keycode == XK_q)
		handle_rotation_left(vars, &vars->map->rot_z);
	else if (keycode == XK_e)
		handle_rotation_right(vars, &vars->map->rot_z);
}
