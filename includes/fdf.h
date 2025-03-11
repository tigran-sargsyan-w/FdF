/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:05:38 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/11 19:47:19 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "event_masks.h"
# include "events.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "keys.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include "parsing.h"
# include "rendering.h"
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <time.h> // delete

// Constants
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define MOVE_SPEED 10
# define ROTATION_SPEED 5
# define ZOOM_IN_FACTOR 1.1f
# define ZOOM_OUT_FACTOR 0.9f
# define Z_FACTOR 1.0
# define M_PI 3.14159265358979323846
# define MIN_ZOOM 0.3
# define MAX_ZOOM 7.0
# define DEFAULT_COLOR 0xFFFFFF

// Structure to hold image data
typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_data		img;
	t_map		*map;
	double		zoom;
	double		rotation;
}				t_vars;

typedef struct s_draw_context
{
	t_data		*img;
	t_map		*map;
	int			x_offset;
	int			y_offset;
	int			line_color;
}				t_draw_context;

// Reordering
void			adjust_initial_scale(t_map *map);
void			error_exit(char *msg);
int				create_argb(int a, int r, int g, int b);
void			draw_grid(t_vars vars);
t_map			*parse_file(const char *filename);
float			deg_to_rad(float angle);
t_point2d		iso_projection(t_point pt);
void			compute_bounding_box(t_map *map, t_bbox *box);
void			draw_line(t_data *img, t_point2d start, t_point2d end,
					int color);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_point2d		get_projected_point(int x, int y, int z, t_draw_context *ctx);
t_draw_context	create_draw_context(t_vars *vars);
t_point			get_center(t_map *map);
t_point2d		translate_point(t_point2d point, t_map *map);
t_point			rotate_point(t_point p, t_map *map);
void			subscribe_to_events(t_vars *vars);
void			update_projected_points(t_map *map);

// Event handling
void			handle_zoom(t_vars *vars, int keycode);
void			handle_rotation(t_vars *vars, int keycode);
void			handle_translation(t_vars *vars, int keycode);
void			handle_exit(t_vars *vars, int keycode);

// Event handling utils
void			update_image(t_vars *vars);
void			apply_zoom(t_map *map, float factor);

// Cleanup
void			cleanup_and_exit(t_vars *vars);

#endif