/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npatron <npatron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:19:11 by morgane           #+#    #+#             */
/*   Updated: 2025/01/20 20:58:35 by npatron          ###   ########.fr       */
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

#define EXTENSION "Map extension is not valid. Please use \".cub\" extension.\n"
#define OPENFD "Map file descriptor is not valid\n"
#define MALLOC "Allocation failed\n"
#define ID_TXT "Texture id is not valid \n"
#define ID_COLORS "Color id is not valid \n"
#define NUM_RGB "There are too much arguments, please respect RGB format\n"
#define RGB_COMA_FORMAT "RGB format is not valid because of comas' or arguments' number\n"
#define CHAR_NOT_VALID "Character invalid in the map\n"
#define STARTING_POINT "Starting point not valid\n"
#define TXT_AFTER_MAP "Textures and colors have to be before your map\n"

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
} t_data;

// PARSING
void	err(char *str);
bool	is_valid_data_extension(char *argv);
int count_lines_fd(char *argv);
void	copy_cub_file(char *argv, t_data *data);
char	*find_textures_paths(char *file, char *txt);
void	extract_textures(t_data *data);
int	*find_rgb_colors(char *file, int *colors);
void	extract_colors(t_data *data);
bool	are_colors_and_textures_before_map(t_data *data);
void	save_map(char **file, char ***map, int *map_lines, int *map_start);
void parsing_cub(char *argv);
void	check_starting_point(char **map, int map_lines);

// PARSING MAP
void    map_line_max_lenght(char **map);


// UTILS
void    print_char_tab(char **tab);

//FREE
void    free_char_tab(char **tab);


#endif