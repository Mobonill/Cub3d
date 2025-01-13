/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morgane <morgane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:21:50 by morgane           #+#    #+#             */
/*   Updated: 2025/01/13 23:41:33 by morgane          ###   ########.fr       */
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

void	find_textures_paths(char *file, char *txt)
{
	int j;
	int len;
	int	start;

	j = 0;
	(void)txt;
	while (file[j] && (file[j] == '\t' || file[j] == ' '))
		j++;
	j += 2;
	if (file[j] != '\t' && file[j] != ' ')
		err(ID);
	while (file[j] && (file[j] == '\t' || file[j] == ' '))
		j++;
	start = j;
	while (file[j] && (file[j] != '\t' || file[j] != ' '))
	{
		len++;
		j++;
	}
	txt = ft_substr(file, start, len);
}

void	extract_textures(t_data *data)
{
	int	i;

	i = 0;
	while (data->file[i])
	{
		if (ft_strncmp(data->file[i], "NO", 2) == 0)
			find_textures_paths(data->file[i], data->no_txt);
		else if (ft_strncmp(data->file[i], "SO", 2) == 0)
			find_textures_paths(data->file[i], data->so_txt);
		else if (ft_strncmp(data->file[i], "WE", 2) == 0)
			find_textures_paths(data->file[i], data->we_txt);
		else if (ft_strncmp(data->file[i], "EA", 2) == 0)
			find_textures_paths(data->file[i], data->ea_txt);
		i++;
	}
}
void	extract_colors(t_data *data)
{
	int	i;

	i = 0;
	while (data->file[i])
	{
		if (ft_strncmp(data->file[i], "F", 1) == 0)
			find_colors_rgb(data->file[i], data->f_color);
		else if (ft_strncmp(data->file[i], "C", 1) == 0)
			find_colors_rgb(data->file[i], data->c_color);
		i++;
	}
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
	copy_cub_file(argv, data);
	extract_textures(data);
	// FREE TEXTURES;
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