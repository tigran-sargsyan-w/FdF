/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:05:38 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/06 17:41:22 by tsargsya         ###   ########.fr       */
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

// Constants
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define MOVE_SPEED 10
# define ISO_ANGLE 0.523599
# define Z_FACTOR 1.0

// Structure to hold image data
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_map	*map;
	double	zoom;
	double	rotation;
}			t_vars;

typedef struct s_draw_context
{
	t_data	*img;
	t_map	*map;
	int		x_offset;
	int		y_offset;
	int		line_color;
}			t_draw_context;

int			create_argb(int a, int r, int g, int b);
void		fill_screen(t_vars *vars, int color);
void		error_exit(char *msg);
t_map		*parse_file(const char *filename);
void		draw_grid(t_vars vars, int line_color);
void		adjust_scale(t_map *map);

#endif