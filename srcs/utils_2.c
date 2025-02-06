/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morgane <morgane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:11:01 by morgane           #+#    #+#             */
/*   Updated: 2025/02/05 19:04:41 by morgane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_starting_point(char **map, int i, int j)
{
	if (map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E'
		|| map[i][j] == 'N')
		return (true);
	else
		return (false);
}

void	check_colors(char *file)
{
	int	i;
	int	coma;

	i = 1;
	coma = 0;
	while (file[i])
	{
		if (file[i] == ',')
		{
			coma++;
			i++;
		}
		else if (file[i] == '-')
			err(RGB_SUP);
		else if (file[i] == '\t' || file[i] == ' '
			|| (file[i] >= '0' && file[i] <= '9'))
			i++;
		else
			err(RGB_COMA_FORMAT);
	}
	if (coma != 2)
		err(RGB_COMA_FORMAT);
	return ;
}

void	color_is_valid(int *color)
{
	int	i;

	i = 0;
	if (color)
	{
		while (i < 3)
		{
			if (color[i] > 255) //60
				err(RGB_SUP);
			i++;
		}
	}
	return ;
}
