/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:05:38 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/19 12:53:55 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "fdf_defs.h"
# include "fdf_types.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <X11/X.h>
# include <X11/keysymdef.h>
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <time.h> // delete

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	data;
	t_map	*map;
	t_bbox	box;
	t_list	*lines;
	int		screen_width;
	int		screen_height;
	int		shift_pressed;
}			t_vars;

// Reordering
void		error_exit(char *msg);
void		draw_grid(t_vars *vars);
void		parse_file(t_vars *vars, const char *filename);
void		init_map(t_vars *vars);
float		deg_to_rad(float angle);
t_point2d	to_isometric(t_point pt, float flattern_factor);
t_point2d	to_orthographic(t_point pt);
t_point2d	to_parallel(t_point pt);
void		compute_bounding_box(t_vars *vars);
void		draw_pixel(t_vars *vars, t_point2d point, int color);
t_point		rotate_point(t_point point, t_map *map);
void		subscribe_to_events(t_vars *vars);

// Event handling
void		handle_zoom(t_vars *vars, int keycode);
void		handle_rotation(t_vars *vars, int keycode);
void		handle_translation(t_vars *vars, int keycode);
void		handle_exit(t_vars *vars, int keycode);
void		handle_flatten(t_vars *vars, int keycode);
void		handle_projection_mode(t_vars *vars, int keycode);
void		handle_reset(t_vars *vars, int keycode);

// Event handling utils
void		update_scene(t_vars *vars);
void		apply_zoom(t_map *map, float factor);
void		apply_flatten(t_map *map, float factor);

// Cleanup
void		cleanup_and_exit(t_vars *vars);

// Menu
void		draw_menu(t_vars *vars);

#endif