/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:15:24 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/07 16:39:57 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	on_keydown(int keycode, t_vars *vars)
{
	handle_exit(vars, keycode);
	handle_translation(vars, keycode);
	handle_rotation(vars, keycode);
	handle_zoom(vars, keycode);
	update_image(vars);
	return (0);
}

int	on_close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

void	subscribe_to_events(t_vars *vars)
{
	mlx_hook(vars->win, ON_KEYDOWN, KEY_PRESS_MASK, on_keydown, vars);
	mlx_hook(vars->win, ON_DESTROY_NOTIFY, NO_EVENT_MASK, on_close_window,
		vars);
}
