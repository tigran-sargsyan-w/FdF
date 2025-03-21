/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:49:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/21 11:33:12 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_map(t_map *map);
static void	free_all_resources(t_vars *vars);

/**
 * @brief Frees the map structure and its associated data.
 * @param map Structure to the map data.
 */
static void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		if (map->values && map->values[i])
			free(map->values[i]);
		if (map->colors && map->colors[i])
			free(map->colors[i]);
		if (map->render_points && map->render_points[i])
			free(map->render_points[i]);
		i++;
	}
	if (map->values)
		free(map->values);
	if (map->colors)
		free(map->colors);
	if (map->render_points)
		free(map->render_points);
	free(map);
}

/**
 * @brief Frees all resources allocated for the program.
 * @param vars Structure containing main variables.
 */
static void	free_all_resources(t_vars *vars)
{
	if (!vars)
		return ;
	if (vars->data.img)
		mlx_destroy_image(vars->mlx, vars->data.img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	if (vars->mlx)
		free(vars->mlx);
	if (vars->lines)
		ft_lstclear(&vars->lines, free);
	if (vars->map)
		free_map(vars->map);
}

/**
 * @brief Cleans up resources and exits the program with an error message.
 * @param vars Structure containing main variables.
 * @param msg Error message to be displayed.
 */
void	cleanup_and_error_exit(t_vars *vars, char *msg)
{
	free_all_resources(vars);
	perror(msg);
	exit(EXIT_FAILURE);
}

/**
 * @brief Cleans up resources and exits the program successfully.
 * @param vars Structure containing main variables.
 */
void	cleanup_and_exit(t_vars *vars)
{
	free_all_resources(vars);
	exit(EXIT_SUCCESS);
}
