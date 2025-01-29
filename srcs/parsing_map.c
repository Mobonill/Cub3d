/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morgane <morgane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:24:05 by morgane           #+#    #+#             */
/*   Updated: 2025/01/29 17:51:26 by morgane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int map_line_max_lenght(char **map)
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
	data->new_map = create_new_map(data, max_len, data->new_map, x_lines);
	printf("apres : \n");
	print_char_tab(data->new_map);
	free(x_lines);
	
}
char	*create_first_and_bottom_lines(int max_len, char *x_lines)
{
	int	j;

	j = 0;
	x_lines = malloc(sizeof(char) * (max_len + 3));
	if (!x_lines)
		err(MALLOC);
	while (j <= max_len)
	{
		x_lines[j] = 'X';
		j++;
	}
	x_lines[j] = '\0';
	return (x_lines);
}

char	*fill_line(char *map, int len)
{
	char 	*res;
	int		i;
	int 	j;
	
	i = 0;
	j = 1;
	
	res = malloc(sizeof(char) * (len + 3));
	res[0] = 'X';
	while (map[i])
	{
		if (map[i] == '1' || map[i] == '0')
			res[j] = map[i];
		else
			res[j] = 'X';
		j++;
		i++;
	}
	while (j <= len) {
		res[j] = 'X';
		j++;
	}
	res[j] = '\0';
	return (res);
}
char **create_new_map(t_data *data, int max_len, char **new_map, char *x_lines)
{
	int		i;
	int		j;

	i = 0;
	j = 1;

	printf("AVANT ----> \n\n");
	print_char_tab(data->map);
	new_map = malloc(sizeof(char *) * (data->map_lines + 3));
	new_map[0] = x_lines;
	while (data->map[i])
	{
		new_map[j] = fill_line(data->map[i], max_len);
		j++;
		i++;
	}
	new_map[j] = ft_strdup(x_lines);
	new_map[j + 1] = NULL;
	return (new_map);
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
		while (new_map[i][j])
		{
			if (new_map[i][j] == '0')
			{
				if ((new_map[i - 1][j] != '1'  && new_map[i - 1][j] != '0') || (new_map[i][j - 1] != '1' && new_map[i][j - 1] != '0'))
					return (false);
				if ((new_map[i][j + 1] != '0' && new_map[i][j + 1] != '1') || (new_map[i + 1][j] != '0' && new_map[i + 1][j] != '1'))
					return (false);
				// is position
			}
			j++;
		}
		i++;
	}
	return(true);
}
