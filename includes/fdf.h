/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:05:38 by tsargsya          #+#    #+#             */
/*   Updated: 2025/02/28 20:31:00 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "event_masks.h"
# include "events.h"
# include "keys.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <math.h>

// Constants
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define MOVE_SPEED 10

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
}			t_point;

typedef struct s_win
{
	int		width;
	int		height;
	int		resized_flag;
}			t_win;

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
	int		obj_x;
	int		obj_y;
	t_win	win_info;
	t_data	data;
}			t_vars;

int			create_argb(int a, int r, int g, int b);
void		fill_screen(t_vars *vars, int color);

#endif