/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:52:21 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/05 12:22:31 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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