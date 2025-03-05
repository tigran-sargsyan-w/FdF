/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsargsya <tsargsya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:49:00 by tsargsya          #+#    #+#             */
/*   Updated: 2025/03/05 13:18:33 by tsargsya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Exit the program with an error message
 * @param msg The error message
 */
void	error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
