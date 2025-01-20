/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morgane <morgane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:19:11 by morgane           #+#    #+#             */
/*   Updated: 2025/01/16 16:48:24 by morgane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <stdbool.h>

#define EXTENSION "Map extension is not valid. Please use \".cub\" extension.\n"
#define OPENFD "Map file descriptor is not valid\n"
#define MALLOC "Allocation failed\n"
#define ID_TXT "Texture id is not valid \n"
#define ID_COLORS "Color id is not valid \n"
#define NUM_RGB "There are too much arguments, please respect RGB format\n"
#define RGB_COMA_FORMAT "RGB format is not valid because of comas' or arguments' number\n"

typedef struct s_data
{
    int     *f_color;
    int     *c_color;
    char    **file;
    char    *no_txt;
    char    *so_txt;
    char    *we_txt;
    char    *ea_txt;
    char    **map;
}   t_data ;


// UTILS
void    print_char_tab(char **tab);

//FREE
void    free_char_tab(char **tab);


#endif