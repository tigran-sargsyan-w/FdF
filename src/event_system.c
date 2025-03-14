/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:15:24 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/14 18:29:48 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	on_keydown(int keycode, t_vars *vars)
{
	handle_exit(vars, keycode);
	handle_translation(vars, keycode);
	handle_rotation(vars, keycode);
	handle_big_rotation(vars, keycode);
	handle_zoom(vars, keycode);
	handle_flatten(vars, keycode);
	handle_projection_mode(vars, keycode);
	handle_reset(vars, keycode);
	update_projected_points(vars->map);
	update_image(vars);
	return (0);
}

int	on_mousedown(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	handle_mouse_zoom(vars, button);
	update_projected_points(vars->map);
	update_image(vars);
	return (0);
}

int	on_close_window(t_vars *vars)
{
	cleanup_and_exit(vars);
	return (0);
}

void	subscribe_to_events(t_vars *vars)
{
	mlx_hook(vars->win, ON_KEYDOWN, KEY_PRESS_MASK, on_keydown, vars);
	mlx_hook(vars->win, ON_MOUSEDOWN, BUTTON_PRESS_MASK, on_mousedown, vars);
	mlx_hook(vars->win, ON_DESTROY_NOTIFY, NO_EVENT_MASK, on_close_window,
		vars);
}
