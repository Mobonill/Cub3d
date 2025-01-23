/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morgane <morgane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:19:11 by morgane           #+#    #+#             */
/*   Updated: 2025/01/23 16:49:25 by morgane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
// # include <X11/keysym.h>
// # include <X11/X.h>
# include <fcntl.h>
# include <stdbool.h>

#define EXTENSION "Error: Map extension is not valid. Please use \".cub\" extension.\n"
#define OPENFD "Error: Map file descriptor is not valid\n"
#define MALLOC "Error: Allocation failed\n"
#define ID_TXT "Error: Texture id is not valid \n"
#define ID_COLORS "Error: Color id is not valid \n"
#define NUM_RGB "Error: RGB arguments' number invalid, please respect RGB format\n"
#define RGB_COMA_FORMAT "Error: RGB format is not valid because of comas' or arguments' number\n"
#define CHAR_NOT_VALID "Error: Character invalid in the map\n"
#define STARTING_POINT "Error: Starting point not valid\n"
#define TXT_AFTER_MAP "Error: Textures and colors have to be before your map\n"
#define MAP_OPENED "Error: Map is opened\n"
#define MAP_INVALID "Error : No valid map found\n"
#define RGB_SUP "Error: RGB colors are between 0 and 255\n"

typedef struct s_data
{
	int		map_lines;
	int		map_start;
	int		*f_color;
	int		*c_color;
	char	**file;
	char	*no_txt;
	char	*so_txt;
	char	*we_txt;
	char	*ea_txt;
	char	**map;
	char	**new_map;
} t_data;

// PARSING
void	err(char *str);
bool	is_valid_data_extension(char *argv);
int count_lines_fd(char *argv);
void	copy_cub_file(char *argv, t_data *data);
char	*find_textures_paths(char *file, char *txt);
void	extract_textures(t_data *data);
int		*find_rgb_colors(char *file, int *colors, int k, int i);
void	extract_valid_colors(t_data *data);
bool	are_colors_and_textures_before_map(t_data *data);
void	save_map(char **file, char ***map, int *map_lines, int *map_start);
void parsing_cub(char *argv);
void	check_starting_point(char **map, int map_lines);

// PARSING MAP
void	parsing_map(t_data *data);
int   map_line_max_lenght(char **map);
void	fullfil_map_with_x(char **map, int len_max, int height);
void	create_new_map(t_data *data, int max_len, char **new_map, char *x_lines);
char	*create_first_and_bottom_lines(int max_len, char *x_lines);
bool	is_map_closed(char **new_map);

// UTILS
void    print_char_tab(char **tab);
void	initialise_data_structure(t_data *data);

//FREE
void    free_char_tab(char **tab);


#endif