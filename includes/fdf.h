/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:05:38 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/05 13:25:31 by tsargsya         ###   ########.fr       */
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
# include <math.h>
# include <stdlib.h>

// Constants
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define MOVE_SPEED 10
# define ISO_ANGLE 0.523599

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_map	*map;
}			t_vars;

// Structure to hold image data
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

int			create_argb(int a, int r, int g, int b);
void		fill_screen(t_vars *vars, int color);
void		error_exit(char *msg);
t_map		*parse_file(const char *filename);
t_point2d	iso_projection(t_point pt, double angle);
void		draw_line(t_data *img, t_point2d start, t_point2d end, int color);

#endif