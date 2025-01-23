/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_and_colors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morgane <morgane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:47:29 by mobonill          #+#    #+#             */
/*   Updated: 2025/01/23 16:49:16 by morgane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*find_textures_paths(char *file, char *txt)
{
	int j;
	int len;
	int	start;

	j = 0;
	len =0;
	(void)txt;
	while (file[j] && (file[j] == '\t' || file[j] == ' '))
		j++;
	j += 2;
	if (file[j] != '\t' && file[j] != ' ')
		err(ID_TXT);
	while (file[j] && (file[j] == '\t' || file[j] == ' '))
		j++;
	if (file[j] == '\n' && file[j + 1] == '\0')
		return (err(ID_TXT), NULL);
	start = j;
	while (file[j])
	{
		len++;
		j++;
	}
	txt = ft_substr(file, start, len);
	return (txt);
}

void	extract_textures(t_data *data)
{
	int	i;

	i = 0;
	while (data->file[i] && i < data->map_start)
	{
		if (ft_strncmp(data->file[i], "NO", 2) == 0)
			data->no_txt = find_textures_paths(data->file[i], data->no_txt);
		else if (ft_strncmp(data->file[i], "SO", 2) == 0)
			data->so_txt = find_textures_paths(data->file[i], data->so_txt);
		else if (ft_strncmp(data->file[i], "WE", 2) == 0)
			data->we_txt = find_textures_paths(data->file[i], data->we_txt);
		else if (ft_strncmp(data->file[i], "EA", 2) == 0)
			data->ea_txt = find_textures_paths(data->file[i], data->ea_txt);
		i++;
	}
}

int	*find_rgb_colors(char *file, int *colors, int k, int i)
{
	char	**save;
	char	*parsed;
	int		j;
	int		start;

	save = ft_split(file, ',');
	colors = malloc(sizeof(int) * 3);
	while(save[++i])
	{
		j = 0;
		while(save[i][j] && (save[i][j] < '0' || save[i][j] > '9'))
			j++;
		if (save[i][j - 1] == '-')
			err(RGB_SUP);
		start = j;
		while(save[i][j] && save[i][j] >= '0' && save[i][j] <= '9')
			j++;
		if ((j - start) > 0)
		{
			if ((j - start) > 3)
				err(RGB_SUP);
			parsed = ft_substr(save[i], start, j - start);
			colors[k++] = ft_atoi(parsed);
			free(parsed);
		}
		while(save[i][j++])
			if (save[i][j] != ' ' && save[i][j] != '\t' && save[i][j] != '\0')
				err(NUM_RGB);
	}
	return (colors);
}


void	extract_valid_colors(t_data *data)
{
	int	i;

	i = 0;
	while (data->file[i] && i < data->map_start)
	{
		if (ft_strncmp(data->file[i], "F", 1) == 0)
			data->f_color = find_rgb_colors(data->file[i], data->f_color, 0, -1);
		else if (ft_strncmp(data->file[i], "C", 1) == 0)
			data->c_color = find_rgb_colors(data->file[i], data->c_color, 0, -1);
		i++;
	}
	i = 0;
	while(data->c_color[i])
	{
		if (data->c_color[i] > 255)
			err(RGB_SUP);
		i++;
	}
	i = 0;
	while(data->f_color[i])
	{
		if (data->f_color[i] > 255)
			err(RGB_SUP);
		i++;
	}
}

bool	are_colors_and_textures_before_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->file[i])
	{
		j = 0;
		while (data->file[i][j] == ' ' || data->file[i][j] == '\t')
			j++;
		if (data->file[i][j] == '1')
		{
			while (data->file[i][j] && (data->file[i][j] == '1' || data->file[i][j] == ' ' || data->file[i][j] == '\t'))
				j++;
			if (data->file[i][j] == '\0')
			{
				if (data->no_txt && data->so_txt && data->we_txt && data->ea_txt && data->c_color && data->f_color)
					return (true);
				else
					return (false);
			}
		}
		i++;
	}
	return (false);
}
