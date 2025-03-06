/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:35:14 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/06 21:11:40 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_map
{
	int		**values;
	float	scale;
	int		columns;
	int		rows;
	float	zoom_factor;
	float	rot_x;
	float	rot_y;
	float	rot_z;
	float	trans_x;
	float	trans_y;
}			t_map;

#endif