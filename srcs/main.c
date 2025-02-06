/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morgane <morgane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:23:50 by morgane           #+#    #+#             */
/*   Updated: 2025/02/05 19:02:13 by morgane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_data(t_data *data)
{
	data->file = NULL;
	data->c_color = NULL;
	data->f_color = NULL;
	data->no_txt = NULL;
	data->so_txt = NULL;
	data->ea_txt = NULL;
	data->we_txt = NULL;
	data->new_map = NULL;
	data->x_pos = 0;
	data->y_pos = 0;
	data->map_lines = 0;
	data->map_start = -1;
	data->end_map = -1;
}

void	parsing_cub(char *argv)
{
	t_data	*data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		err(MALLOC);
	init_data(data);
	if (!is_valid_data_extension(argv))
		err(EXTENSION);
	copy_cub_file(argv, data);
	where_is_the_map(data, data->file, &data->map_lines);
	save_map(data, data->file, &data->map, &data->map_lines);
	extract_textures(data);
	extract_valid_colors(data);
	if (are_colors_and_textures_before_map(data, 0) == false)
		err(TXT_AFTER_MAP);
	file_is_clean(data);
	parsing_map(data);
	free(data->c_color);
	free(data->f_color);
	free(data->ea_txt);
	free(data->no_txt);
	free(data->so_txt);
	free(data->we_txt);
	free_char_tab(data->map);
	free_char_tab(data->new_map);
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
