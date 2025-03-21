/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:15:24 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/21 11:31:35 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	on_keydown(int keycode, t_vars *vars);
static int	on_keyup(int keycode, t_vars *vars);
static int	on_mousedown(int button, int x, int y, t_vars *vars);
static int	on_close_window(t_vars *vars);

/**
 * @brief Handles on key press events.
 * @param keycode Pressed key code.
 * @param vars Structure containing main variables.
 * @return 0 on success.
 */
static int	on_keydown(int keycode, t_vars *vars)
{
	if (keycode == XK_Shift_L)
		vars->shift_pressed = 1;
	handle_exit(vars, keycode);
	handle_translation(vars, keycode);
	handle_rotation(vars, keycode);
	handle_zoom(vars, keycode);
	handle_flatten(vars, keycode);
	handle_projection_mode(vars, keycode);
	handle_reset(vars, keycode);
	update_scene(vars);
	return (0);
}

/**
 * @brief Handles on key release events.
 * @param keycode Released key code.
 * @param vars Structure containing main variables.
 * @return 0 on success.
 */
static int	on_keyup(int keycode, t_vars *vars)
{
	if (keycode == XK_Shift_L)
		vars->shift_pressed = 0;
	return (0);
}

/**
 * @brief Handles mouse button press events.
 * @param button Pressed button code.
 * @param x X coordinate of the mouse.
 * @param y Y coordinate of the mouse.
 * @param vars Structure containing main variables.
 * @return 0 on success.
 */
static int	on_mousedown(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	handle_zoom(vars, button);
	update_scene(vars);
	return (0);
}

/**
 * @brief Handles window close events.
 * @param vars Structure containing main variables.
 * @return 0 on success.
 */
static int	on_close_window(t_vars *vars)
{
	cleanup_and_exit(vars);
	return (0);
}

/**
 * @brief Subscribes to events in the window.
 * @param vars Structure containing main variables.
 */
void	subscribe_to_events(t_vars *vars)
{
	mlx_hook(vars->win, KeyPress, KeyPressMask, on_keydown, vars);
	mlx_hook(vars->win, KeyRelease, KeyReleaseMask, on_keyup, vars);
	mlx_hook(vars->win, ButtonPress, ButtonPressMask, on_mousedown, vars);
	mlx_hook(vars->win, DestroyNotify, NoEventMask, on_close_window, vars);
}
