/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morgane <morgane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:21:50 by morgane           #+#    #+#             */
/*   Updated: 2025/01/19 20:11:23 by morgane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	err(char *str)
{
	while (*str)
		write(2, str++, 1);
	exit(1);
}

bool	is_valid_data_extension(char *argv)
{
	int	i;

	i = ft_strlen(argv);
	if (i < 5)
		return (false);
	if (argv[i - 1] == 'b' && argv[i - 2] == 'u' && argv[i - 3] == 'c' && argv[i - 4] == '.')
		return (true);
	return (false);
}

int count_lines_fd(char *argv)
{
    char	*line;
    int		len;
	int		fd;

	line = NULL;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		err(OPENFD);
    while ((line = get_next_line(fd)) != NULL)
    {
        len++;
        free(line);
    }
	close(fd);
    return (len);
}

void	copy_cub_file(char *argv, t_data *data)
{
	int		i;
	int		fd;
	char	*line;

	line = NULL;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		free(line);
		err(OPENFD);
	}
	i = count_lines_fd(argv);
	data->file = malloc(sizeof(char *) * (i + 1));
	if (!data->file)
		err(MALLOC);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		data->file[i++] = ft_strdup(line);
		free(line);
	}
	data->file[i] = NULL;
	close(fd);
	// print_char_tab(data->file);
}

// int	ft_is_whitespace(char *str, int i)
// {
// 	while (str[i] && (str[i] == '\t' || str[i] == ' '))
// 		i++;
// 	return (i);
// }

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
	while (data->file[i])
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
	while (data->file[i])
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
        while (data->file[i][j] == ' ')
            j++;
		if (data->file[i][j] == '1')
		{
			while (data->file[i][j] && (data->file[i][j] == '1' || data->file[i][j] == ' '))
				j++;
			if (data->file[i][j] == '\n' && data->file[i][j + 1] == '\0')
			{
				if (data->no_txt && data->so_txt && data->we_txt)
					return (true);
				else
					return (false);
			}
		}
        i++;
    }
	return (false);
}

void save_map(char **file, char ***map)
{
	int	i;
	int	j;
	int	map_start;
	int	map_lines;

	i = 0;
	map_start = -1;
	map_lines = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t')
			j++;
		if (file[i][j] == '1')
		{
			if (map_start == -1)
				map_start = i;
			map_lines++;
		}
		else if (map_start != -1)
			break;
		i++;
	}
	if (map_start == -1 || map_lines == 0)
		err("Error: No valid map found\n");
	*map = (char **)malloc(sizeof(char *) * (map_lines + 1));
	if (!*map)
		err(MALLOC);
	i = 0;
	while (i < map_lines)
	{
		(*map)[i] = ft_strdup(file[map_start + i]);
		if (!(*map)[i])
			err(MALLOC);
		i++;
	}
	(*map)[i] = NULL;
}

void parsing_cub(char *argv)
{
	t_data	*data;
	int i = 0;

	if (!is_valid_data_extension(argv))
		err(EXTENSION);
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		err(MALLOC);
	data->file = NULL;
	data->c_color = NULL;
	data->f_color = NULL;
	data->no_txt = NULL;
	data->so_txt = NULL;
	data->ea_txt = NULL;
	data->we_txt = NULL;
	copy_cub_file(argv, data);
	extract_textures(data);
	extract_colors(data);
	if (are_colors_and_textures_before_map(data) == true)
		printf("true");
	else
		printf("false");
	save_map(data->file, &data->map);
	// FREE TEXTURES;
	// FREE COLORS;
	// FREE MAP
	free_char_tab(data->file);
	free(data);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	parsing_cub(argv[1]);
	return (0);
}