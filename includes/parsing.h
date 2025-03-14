/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:35:14 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/15 17:41:48 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "fdf.h"
# include "rendering.h"

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
	t_point2d			**projected_points;
	t_projection_mode	projection_mode;
}						t_map;

#endif