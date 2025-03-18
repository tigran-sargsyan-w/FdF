/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:52:21 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/18 22:05:11 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

typedef struct s_point
{
	int			x;
	int			y;
	int			z;
}				t_point;

typedef struct s_point2d
{
	int			x;
	int			y;
}				t_point2d;

// Structure for line drawing parameters (Bresenham)
typedef struct s_line_params
{
	int			delta_x;
	int			delta_y;
	int			step_x;
	int			step_y;
	int			error;
}				t_line_params;

// Structure representing a line with its two endpoints
typedef struct s_line
{
	t_point2d	start;
	t_point2d	end;
}				t_line;

// Structure for bounding box
typedef struct s_bbox
{
	int			min_x;
	int			max_x;
	int			min_y;
	int			max_y;
}				t_bbox;

typedef enum e_projection_mode
{
	ISO,
	PARALLEL,
	ORTHO
}						t_projection_mode;

typedef struct s_map
{
	int					**values;
	int					**colors;
	float				scale;
	int					columns;
	int					rows;
	float				zoom_factor;
	float				flatten_factor;
	float				rot_x;
	float				rot_y;
	float				rot_z;
	float				trans_x;
	float				trans_y;
	t_point2d			**render_points;
	t_projection_mode	projection_mode;
}						t_map;

#endif