/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:21:50 by morgane           #+#    #+#             */
/*   Updated: 2025/01/20 20:13:50 by npatron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
}

void	save_map(char **file, char ***map, int *map_lines, int *map_start)
{
	int	i;
	int	j;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t')
			j++;
		if (file[i][j] == '1')
		{
			if (*map_start == -1)
				*map_start = i;
			(*map_lines)++;
		}
		else if (*map_start != -1)
			break;
		i++;
	}
	if (*map_start == -1 || map_lines == 0)
		err("Error: No valid map found\n");
	*map = (char **)malloc(sizeof(char *) * (*map_lines + 1));
	if (!*map)
		err(MALLOC);
	i = 0;
	while (i < *map_lines)
	{
		(*map)[i] = ft_strdup(file[*map_start + i]);
		if (!(*map)[i])
			err(MALLOC);
		i++;
	}
	(*map)[i] = NULL;
}

void	check_starting_point(char **map, int map_lines)
{
	int	i;
	int	j;
	int	starting_char;

	i = 0;
	j = 0;
	starting_char = 0;
	while(i < map_lines && map[i][j])
	{
		if (map[i][j] == '\n' && map[i][j + 1] == '\0')
		{
			j = 0;
			i++;
		}
		else if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0' && map[i][j] != '\t')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
				starting_char++;
			else
				err(CHAR_NOT_VALID);
		}
		j++;
	}
	if (starting_char != 1)
		err(STARTING_POINT);
}

void parsing_cub(char *argv)
{
	t_data	*data;

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
	data->map_lines = 0;
	data->map_start = -1;
	copy_cub_file(argv, data);
	save_map(data->file, &data->map, &data->map_lines, &data->map_start);
	extract_textures(data);
	extract_colors(data);
	if (are_colors_and_textures_before_map(data) == false)
		err(TXT_AFTER_MAP);
	check_starting_point(data->map, data->map_lines);
	map_line_max_lenght(data->map);
	// FREE TEXTURES;
	// FREE COLORS;
	// FREE MAP
	free_char_tab(data->file);
	free(data);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	parsing_cub(argv[1]);
	return (0);
}
