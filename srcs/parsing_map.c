/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morgane <morgane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:24:05 by morgane           #+#    #+#             */
/*   Updated: 2025/01/23 16:49:50 by morgane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int   map_line_max_lenght(char **map)
{
    int     i;
    size_t  max;
    size_t  len;

    i = 0;
    max = 0;
    len = 0;
    while (map[i])
    {
        len = ft_strlen(map[i]);
        if (len > max)
            max = len;
        i++;
    }
    return ((int)max);
}


void	parsing_map(t_data *data)
{
	int	max_len;
	char	*x_lines;
	
	x_lines = NULL;
	check_starting_point(data->map, data->map_lines);
	max_len = map_line_max_lenght(data->map);
	x_lines = create_first_and_bottom_lines(max_len, x_lines);
	create_new_map(data, max_len, data->new_map, x_lines);
}
char	*create_first_and_bottom_lines(int max_len, char *x_lines)
{
	int	j;

	j = -1;
	x_lines = malloc(sizeof(char) * (max_len + 2));
	if (!x_lines)
		err(MALLOC);
	while (++j <= max_len + 1)
		x_lines[j] = 'X';
	x_lines[max_len + 2] = '\0';
	return (x_lines);
}
void create_new_map(t_data *data, int max_len, char **new_map, char *x_lines)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	new_map = malloc(sizeof(char *) * (data->map_lines + 3));
	if (!new_map)
		err(MALLOC);
	new_map[0] = x_lines;
	while(i < data->map_lines)
	{
		j = 0;
		k = i + 1;
		new_map[k] = malloc(sizeof(char) * (max_len + 3));
		new_map[k][0] = 'X';
		while (j <= max_len)
		{
			if (data->map[i][j] == '1' || data->map[i][j] == '0')
				new_map[k][j+1] = data->map[i][j];
			else if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W')
				new_map[k][j + 1] = '0';
			else
				new_map[k][j+1] = 'X';
			j++;
		}
		new_map[k][j+1] = '\0';
		i++;
	}
	new_map[k + 1] = ft_strdup(x_lines);
	new_map[data->map_lines + 2] = NULL;
	if (is_map_closed(new_map) == false)
		err(MAP_OPENED);
	free(x_lines);
	
}

bool	is_map_closed(char **new_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(new_map[i])
	{
		j = 0;
		printf("%s\n", new_map[i]);
		while (new_map[i][j])
		{
			if (new_map[i][j] == '0')
			{
				if ((new_map[i - 1][j] != '1'  && new_map[i - 1][j] != '0') || (new_map[i][j - 1] != '1' && new_map[i][j - 1] != '0'))
					return (false);
				if ((new_map[i][j + 1] != '0' && new_map[i][j + 1] != '1') || (new_map[i + 1][j] != '0' && new_map[i + 1][j] != '1'))
					return (false);
			}
			j++;
		}
		i++;
	}
	return(true);
}

