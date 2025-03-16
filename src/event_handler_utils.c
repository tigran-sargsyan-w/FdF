/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:37:35 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/16 14:35:12 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_zoom(t_map *map, float factor)
{
	map->zoom_factor *= factor;
	if (map->zoom_factor < MIN_ZOOM)
		map->zoom_factor = MIN_ZOOM;
	if (map->zoom_factor > MAX_ZOOM)
		map->zoom_factor = MAX_ZOOM;
}

void	apply_flatten(t_map *map, float factor)
{
	map->flatten_factor *= factor;
	if (map->flatten_factor < MIN_FLATTEN)
		map->flatten_factor = MIN_FLATTEN;
	if (map->flatten_factor > MAX_FLATTEN)
		map->flatten_factor = MAX_FLATTEN;
}
