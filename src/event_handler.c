/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:33:39 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/20 21:51:33 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Handles zooming.
 * @param vars Structure containing main variables.
 * @param keycode Pressed key code.
 */
void	handle_zoom(t_vars *vars, int keycode)
{
	if (keycode == XK_KP_Add || keycode == MOUSE_SCROLL_UP)
		apply_zoom(vars->map, ZOOM_IN_FACTOR);
	else if (keycode == XK_KP_Subtract || keycode == MOUSE_SCROLL_DOWN)
		apply_zoom(vars->map, ZOOM_OUT_FACTOR);
}

/**
 * @brief Handles flattening.
 * @param vars Structure containing main variables.
 * @param keycode Pressed key code.
 */
void	handle_flatten(t_vars *vars, int keycode)
{
	if (keycode == XK_Page_Up)
		apply_flatten(vars->map, FLATTEN_DECREMENT);
	else if (keycode == XK_Page_Down)
		apply_flatten(vars->map, FLATTEN_INCREMENT);
}

/**
 * @brief Handles projection mode switching.
 * @param vars Structure containing main variables.
 * @param keycode Pressed key code.
 */
void	handle_projection_mode(t_vars *vars, int keycode)
{
	if (keycode == XK_p)
	{
		if (vars->map->projection_mode == ISO)
			vars->map->projection_mode = ORTHO;
		else if (vars->map->projection_mode == ORTHO)
			vars->map->projection_mode = PARALLEL;
		else
			vars->map->projection_mode = ISO;
	}
}

/**
 * @brief Handles resetting the map.
 * @param vars Structure containing main variables.
 * @param keycode Pressed key code.
 */
void	handle_reset(t_vars *vars, int keycode)
{
	if (keycode == XK_r)
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

/**
 * @brief Handles exiting the program.
 * @param vars Structure containing main variables.
 * @param keycode Pressed key code.
 */
void	handle_exit(t_vars *vars, int keycode)
{
	if (keycode == XK_Escape)
		cleanup_and_exit(vars);
}
