/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbureera <pbureera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:57:45 by pbureera          #+#    #+#             */
/*   Updated: 2023/07/18 15:01:31 by pbureera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180));
}

double	rad_to_deg(double rad)
{
	return (rad * (180 / M_PI));
}
