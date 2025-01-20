/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_and_colors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:47:29 by mobonill          #+#    #+#             */
/*   Updated: 2025/01/20 20:16:07 by npatron          ###   ########.fr       */
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

int	*find_rgb_colors(char *file, int *colors)
{
	int	i;
	char	save[15];
	int		j;
	int		virgule;
	int		k;
	
	i = 0;
	j = 0;
	k = 0;
	virgule = 0;
	colors = malloc(sizeof(int) * 3);
	while (file[i] && (file[i] == '\t' || file[i] == ' '))
		i++;
	i++;
	if (file[i] != '\t' && file[i] != ' ')
		err(ID_COLORS);
	while (file[i])
	{
		j = 0;
		ft_memset(save, 0, sizeof(save));
		if (file[i] == '\t' || file[i] == ' ')
			i++;
		else if (file[i] >= '0' && file[i] <= '9')
		{
			while (file[i] && file[i] >= '0' && file[i] <= '9' && file[i] != ',' && file[i] != '\t' && file[i] != ' ')
				save[j++] = file[i++];
		}
		else if (file[i++] == ',')
			virgule++;
		else
			i++;
		if (j > 0)
			colors[k++] = ft_atoi(save);
	}
	if (virgule != 2)
		err(RGB_COMA_FORMAT);
	return (colors);
}

void	extract_colors(t_data *data)
{
	int	i;

	i = 0;
	while (data->file[i] && i < data->map_start)
	{
		if (ft_strncmp(data->file[i], "F", 1) == 0)
			data->f_color = find_rgb_colors(data->file[i], data->f_color);
		else if (ft_strncmp(data->file[i], "C", 1) == 0)
			data->c_color = find_rgb_colors(data->file[i], data->c_color);
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
		printf("%s", data->file[i]);
		while (data->file[i][j] == ' ' || data->file[i][j] == '\t')
			j++;
		if (data->file[i][j] == '1')
		{
			while (data->file[i][j] && (data->file[i][j] == '1' || data->file[i][j] == ' ' || data->file[i][j] == '\t'))
				j++;
			if (data->file[i][j] == '\n' && data->file[i][j + 1] == '\0')
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
