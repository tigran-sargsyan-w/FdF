/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:37:35 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/20 21:46:09 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Zoom in or out of the map.
 * @param map Structure containing the map data.
 * @param factor Zoom factor.
 */
void	apply_zoom(t_map *map, float factor)
{
	map->zoom_factor *= factor;
	if (map->zoom_factor < MIN_ZOOM)
		map->zoom_factor = MIN_ZOOM;
	if (map->zoom_factor > MAX_ZOOM)
		map->zoom_factor = MAX_ZOOM;
}

/**
 * @brief Flatten in or out the map.
 * @param map Structure containing the map data.
 * @param factor Flatten factor.
 */
void	apply_flatten(t_map *map, float factor)
{
	map->flatten_factor *= factor;
	if (map->flatten_factor < MIN_FLATTEN)
		map->flatten_factor = MIN_FLATTEN;
	if (map->flatten_factor > MAX_FLATTEN)
		map->flatten_factor = MAX_FLATTEN;
}
